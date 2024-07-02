#include "socialmedia.h"

#include <stdlib.h>

Database db;
Cache userCache;
Cache postCache;

void printUser(User *user) {
  printf("User: %d, Username: %s, Followers: %d, Following: %d, Liked: %d\n",
         user->userId, user->username, user->numOfFollowers,
         user->numOfFollowing, user->liked);
}

void printPost(Post *post) {
  printf("Post: %d, Author: %s, Likes: %d\n", post->postId,
         post->author->username, post->likes);
}

void printUserCache() {
  Node *current = userCache.head;
  printf("UserCache:\n");
  for (; current != NULL ; current = current->next)
          printUser((User*) current->data);
}

void printPostCache() {
  Node *current = postCache.tail;
  printf("PostCache:\n");
  for (; current != NULL ; current = current->prev )
      printPost((Post*)current->data);
}

Node *createNode(void *data) {
  Node* address = (Node*) malloc (sizeof(Node));
  address->next = NULL;
  address->data = data;
  address->prev = NULL;

  return address;
}

void appendToCache(Cache *cache, void *data) {
  Node *address = createNode(data);

  if (cache->size >= cache->capacity)
    removeLast(cache);

  if (cache->size == 0){ /* If cache is empty */
    cache->tail = address;
    cache->head = address;
  }

  else {
    cache->head->prev = address;
    address->next = cache->head;
    cache->head = address;
  }

  cache->size++;
}

void moveToFront(Cache *cache, Node *node) {
  if (cache->head == node)
    return;

  if (cache->tail == node) {
    cache->tail = node->prev;
    node->prev->next = NULL;
    node->prev = NULL;
    node->next = cache->head;
    cache->head->prev = node;
  }

  else {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    cache->head->prev = node;

    node->prev = NULL;
    node->next = cache->head;
  }

  cache->head = node;
}

void removeLast(Cache *cache) {
  Node *last;
  if (cache->tail == NULL || cache->size == 0)  return;

  last = cache->tail;
  if (last->prev)
    last->prev->next = NULL;
  else
    cache->head = NULL;  /* if list only has 1 element */

  cache->tail = last->prev;
  cache->size--;
  free(last);
}

User *fetchUser(int userId) {
  int i;
  Node* current = userCache.head;

  for (i = 0; i < userCache.size; i++){
    if (((User *)(current->data))->userId == userId) {
      moveToFront(&userCache, current);
      return userCache.head->data;
    }
    else
      current = current->next;
  }
  /* If the code reached here, it means that it couldn't find it in the cache*/
  for (i = 0; i < DB_USER_CAPACITY; i++)
    if (db.users[i].userId == userId) {
      appendToCache(&userCache, &db.users[i]);
      return userCache.head->data;
    }
  return 0;
}

Node *fetchUserNode(int userId){
  int i;
  Node* current = userCache.head;

  for (i = 0; i < userCache.size; i++){
    if (((User *)(current->data))->userId == userId) {
      moveToFront(&userCache, current);
      return userCache.head;
    }
    else
      current = current->next;
  }
  for (i = 0; i < DB_USER_CAPACITY; i++)
    if (db.users[i].userId == userId) {
      appendToCache(&userCache, &db.users[i]);
      return userCache.head;
    }
  return 0;
}

Post *fetchPost(int postId) {
  int i;
  Node* current = postCache.head;

  for (i = 0; i < postCache.size; i++){
    if (((Post *)(current->data))->postId == postId){
      moveToFront(&postCache, current);
      return postCache.head->data;
    }
    else
      current = current->next;
  }
  for (i = 0; i < DB_POST_CAPACITY; i++)
    if (db.posts[i].postId == postId) {
      appendToCache(&postCache, &db.posts[i]);
      return postCache.head->data;
    }
  return 0;
}

Node *fetchPostNode(int postId) {
  int i;
  Node* current = postCache.head;

  for (i = 0; i < postCache.size; i++){
    if (((Post *)(current->data))->postId == postId){
      moveToFront(&postCache, current);
      return postCache.head;
    }
    else
      current = current->next;
  }
  for (i = 0; i < DB_POST_CAPACITY; i++)
    if (db.posts[i].postId == postId) {
      appendToCache(&postCache, &db.posts[i]);
      return postCache.head;
    }
  return 0;
}

void followUser(int followerId, int followedId) {
  User* follower = fetchUser(followerId);
  User* followed = fetchUser(followedId);

  Node* newNode = createNode(follower);

  if (followed->numOfFollowers == 0){
    followed->followers_head = newNode;
    followed->followers_tail = newNode;
  }
  else if(followed->numOfFollowers == 1){
    followed->followers_tail->next = newNode;
    newNode->prev = followed->followers_tail;
    followed->followers_tail = newNode;
  }
  else {
    followed->followers_tail->next = newNode;
    newNode->prev = followed->followers_tail;
    followed->followers_tail = newNode;
  }

  followed->numOfFollowers++;
  follower->numOfFollowing++;
}

void likePost(int userId, int postId) {
  User* user = fetchUser(userId);
  Post* post = fetchPost(postId);

  user->liked++;
  post->likes++;
}

void printFollowersInReverse() {
  Node *current = userCache.tail;
  Node *currentFollower;

  printf("Followers of all users in UserCache in reverse:\n");
  for (; current != NULL; current = current->prev) {
    printf("Followers of user with id %d in reverse:\n", ((User*)current->data)->userId);

    currentFollower = ((User*)current->data)->followers_tail;
    for (; currentFollower != NULL; currentFollower = currentFollower->prev)
      printf("[%d] ", ((User *) currentFollower->data)->userId);

    printf("\n");
  }
}

void freeLinkedList(Node *head) {
  Node *current = head;
  Node *next;

  while (current){
    next = current->next;
    free(current);
    current = next;
  }
}