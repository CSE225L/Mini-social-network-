# Member 5 Guide — Real-Time Interaction & System Integration

this guide is the explanation of what was built and how it fits with Members 1–4.

---

## Features implemented

### Member 5 (this branch)

- **Array-based circular queue (`InboxQueue`)** for a FIFO **Pending Requests & Notifications** inbox.
- **Array-based stack (`UndoStack`)** for an **Action History** undo system (friend request, accept friend, create post, delete post, block user).
- **`main.cpp` CLI** with a switch-case menu that wires together:
  - Member 1: `User` class + BST user database (register, login, search, list users)
  - Member 2: template `Graph` adjacency lists, alphabetical `SortedList` friend lists, `UnsortedList` blocked users
  - Member 3: linked-list queue BFS (suggestions, degrees of separation), array-stack iterative DFS, recursive DFS communities
  - Member 4: linked-list stack chronological feed, array priority-queue trending feed, post create/like/comment/delete

---

## How the members connect

| Piece | Role in the running program |
| --- | --- |
| `User` / `BST` | Identity. IDs are unique keys. Login and search go through the BST. |
| `Graph<User>` | One vertex per registered user. Friendships are undirected edges stored as linked lists. |
| `SortedList` | Built on demand from a user’s adjacency list, ordered by **name**. |
| `UnsortedList blocked[MAX_USERS]` | Per-user block lists (one list per graph index). |
| `Member3Algorithms` | Needs an adjacency **matrix**. `Graph::BuildAdjMatrix` fills `int matrix[100][100]` from the linked lists. Algorithms print **graph indexes**; the CLI also prints ID/name mapping. |
| `FeedEngine` | Owns all posts, the chronological stack, and the trending heap-like array. |
| `InboxQueue` | Global FIFO of request/notice records; display is filtered by the logged-in user’s ID. |
| `UndoStack` | LIFO of `Action` records so the last successful mutating action can be reversed. |

---

## Member 5 files — block-by-block

### `InboxQueue.h` / `InboxQueue.cpp`

**`Notification` struct**

- `fromID`, `toID`: who sent it and who should see it.
- `type`: `1` = friend request, `2` = general notice.
- `text`: short message shown in the inbox.

**`InboxQueue` data (circular array)**

- `data[MAX_INBOX]` with `MAX_INBOX = 100`.
- `front`: index of the oldest item.
- `rear`: index of the newest item.
- `length`: how many slots are occupied (needed because a circular buffer cannot tell empty from full using only front/rear).

**Constructor**  
Sets `front = 0`, `rear = -1`, `length = 0` (empty queue).

**`isEmpty` / `isFull`**  
Empty when `length == 0`. Full when `length == MAX_INBOX`.

**`enqueue`**  
If full, print an error and return. Otherwise `rear = (rear + 1) % MAX_INBOX`, store the item, increment `length`. First-in stays at `front`; new items go to the back (FIFO).

**`dequeue`**  
If empty, return a zeroed `Notification`. Otherwise copy `data[front]`, then `front = (front + 1) % MAX_INBOX`, decrement `length`. Oldest request/notice comes out first.

**`displayForUser(userID)`**  
Walks `length` items from `front` using wrap-around. Prints only records whose `toID` matches the logged-in user. Requests are labeled `[REQUEST]`; other items `[NOTICE]`.

**`hasPendingRequest(fromID, toID)`**  
Linear scan of the circular buffer for a type-1 record with that pair. Used so we do not enqueue duplicates and so accept only works on a real pending request.

**`removeRequest(fromID, toID)`**  
Copy every item except the **first matching request** into a temporary array, then reset the queue and `enqueue` the survivors. Needed because undo and accept must pull one request out of the middle without using STL lists.

---

### `UndoStack.h` / `UndoStack.cpp`

**Action type constants**

- `ACTION_SEND_REQUEST` (1): undoing removes the pending request from the inbox.
- `ACTION_ACCEPT_FRIEND` (2): undoing calls `Graph::RemoveFriend`.
- `ACTION_CREATE_POST` (3): undoing deletes that post ID from the feed.
- `ACTION_DELETE_POST` (4): undoing restores the saved `Post` object.
- `ACTION_BLOCK_USER` (5): undoing removes the ID from that user’s `UnsortedList`.

**`Action` struct**

- `type`, `userA`, `userB`: meaning depends on type (sender/receiver, or author/postID).
- `savedPost`: used only for delete-post undo so likes/comments/text come back.

**`UndoStack` data**

- `items[MAX_UNDO]` (`MAX_UNDO = 100`).
- `top` starts at `-1` (empty). This is the usual lab array stack.

**`push`**  
If not full, `top++` and store the action (LIFO: last action is undone first).

**`pop`**  
If empty, print “Nothing to undo” and return a zeroed action. Otherwise return `items[top]` and `top--`.

---

### `main.cpp` — the integrator

**Includes**  
Pulls Member 1 (`User.h`, `BST.h`), Member 2 (`Graph.h`, `SortedList.h`, `UnsortedList.h`), Member 3 (`Member3Algorithms.h`), Member 4 (`FeedEngine.h`), and Member 5 (`InboxQueue.h`, `UndoStack.h`). `<iostream>` / `<string>` only; no banned containers.

**`printMenu()`**  
Prints choices `0`–`23`. The switch below uses the same numbers.

**`main()` object graph**

- `BST userDB` — all registered users, ordered by ID.
- `Graph<User> network(MAX_USERS)` — vertices + friend linked lists (`MAX_USERS` is 100 from `Graph.h`).
- `UnsortedList blocked[MAX_USERS]` — block list for each graph index.
- `Member3Algorithms algo` — BFS/DFS helpers.
- `FeedEngine feed` — posts and both feeds.
- `InboxQueue inbox` — global FIFO inbox.
- `UndoStack history` — undo stack.
- `currentID` — `-1` means logged out; otherwise the logged-in user’s ID.

**Input loop**  
Prints who is logged in, shows the menu, reads `choice`. If `cin` fails (non-numeric), it clears the error and continues. `cin.ignore` after numbers so later `getline` for post text works.

**`switch (choice)`**

| Case | Behavior |
| --- | --- |
| **1 Register** | Read ID, name, VIP flag. Reject duplicate IDs via `userDB.searchByID`. `userDB.insert` then `network.AddUser` so BST and graph stay aligned (graph index = order of registration). |
| **2 Login** | BST lookup by ID. On success set `currentID`. |
| **3 Logout** | `currentID = -1`. |
| **4 Search** | BST search; print the `User` or “not found”. |
| **5 Display all** | In-order BST walk (sorted by ID). |
| **6 Send friend request** | Requires login. Rejects self, missing user, block in either direction, already-friends, and duplicate pending request. Enqueues a type-1 request and a type-2 notice to the target, then pushes `ACTION_SEND_REQUEST`. |
| **7 View inbox** | `inbox.displayForUser(currentID)`. Oldest matching items appear first because the queue is FIFO. |
| **8 Accept request** | Requires a pending type-1 from `fromID` to `currentID`. `network.AddFriend` on both indexes, `removeRequest`, notice to the sender, `ACTION_ACCEPT_FRIEND` on the stack. |
| **9 Friends alphabetical** | Copies friend IDs from the graph, inserts those `User` objects into a fresh `SortedList` (by name), prints it. |
| **10 Block** | Inserts into `blocked[myIndex]`, drops the friendship if it exists, pushes `ACTION_BLOCK_USER`. Send-request later checks both block lists. |
| **11 Show blocked** | Prints that user’s unsorted block list. |
| **12 Friend suggestions** | Builds the adjacency matrix, runs Member 3 BFS “friends of friends” (level == 2), then prints index → ID/name. |
| **13 Mutual friends** | Matrix + Member 3 scan of shared neighbors (indexes). |
| **14 Degrees of separation** | Member 3 BFS distance; `-1` means disconnected. |
| **15 Communities** | Recursive DFS components, then iterative DFS from index 0 using Member 3’s array stack. |
| **16 Create post** | `feed.createPost(...)` using the logged-in `User`. Pushes `ACTION_CREATE_POST` with `userB = postID`. |
| **17 Delete post** | Only the author can delete. Saves the `Post` into the undo action (`ACTION_DELETE_POST`). |
| **18 / 19** | Like / comment by post ID (Member 4 trending order updates by engagement). |
| **20 / 21** | Chronological (LIFO stack, newest first) and trending (array kept sorted by likes+comments). |
| **22 Friends feed** | Posts whose author ID is in the current user’s friend ID array. |
| **23 Undo** | `history.pop()` then reverse that action (see table below). |
| **0** | Exit. |
| **default** | Unknown choice. |

**Undo reverse mapping**

| Stored type | Reverse |
| --- | --- |
| Send request | `inbox.removeRequest(userA, userB)` |
| Accept friend | `network.RemoveFriend` on those two indexes |
| Create post | `feed.deletePost(userB, ...)` |
| Delete post | `feed.restorePost(savedPost)` |
| Block user | `blocked[userA's index].RemoveID(userB)` |

Undo is one step at a time (top of stack only), which is what an array stack is for.

---

## Supporting modules brought in for a working CLI

Members 1–4’s branches were incomplete or did not compile as-is (mismatched names, missing methods, `cout<<=` typo, placeholder `user.h` / `graph.h` on Member 4). This branch uses the **same data structures they were assigned**, with APIs aligned so `main.cpp` can call them:

- **Member 1:** `User` with `<`, `>`, `==` on ID; `getID` / `getName` / VIP; BST insert/search/in-order.
- **Member 2:** `LinkedList<T>` adjacency lists; `Graph<T>` add user/friend, show/copy friends, build matrix; sorted friends; unsorted blocks.
- **Member 3:** linked-list `Queue` for BFS; array `Stack` for iterative DFS; recursive DFS communities; BFS suggestions and BFS distance.
- **Member 4:** `Post`; `LinkedStack` chronological feed; `TrendingFeed` array “priority queue” by engagement; `FeedEngine` create/like/comment/delete/restore.

---


Typical flow: register a few users → login → send request → other user login → view inbox → accept → create/like posts → open chronological and trending feeds → undo.
