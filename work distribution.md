Work Distribution Plan

**Member 1: User Database & Identity Manager**

* **Role:** You are the gatekeeper. You build the core data entities and handle how the system stores and searches for users.
* **Features:** User Registration, Login System, Fast User Lookup.
* **Required DSA Concepts:**
* **Classes and Objects:** Design the `User` class (ID, Name, VIP status).
* **Operator Overloading:** Overload `<`, `>`, and `==` so the system can easily compare user names or IDs.
* **Binary Search Tree (BST):** Store all registered users in a BST. This ensures searching for a user takes $O(\log n)$ time instead of $O(n)$.



**Member 2: Network Infrastructure & Connection Manager**

* **Role:** You build the actual "network" part of the social network and manage user lists.
* **Features:** Friendship Graph, Alphabetical Friend Lists, Blocked User Lists.
* **Required DSA Concepts:**
* **Template Class & Graph:** Build an Adjacency List graph using templates (`template <class T> class Graph`).
* **Linked List:** Use custom linked lists for the adjacency list (each user points to a list of friends).
* **Sorted & Unsorted Lists:** Implement a Sorted List (Array or LL) to display a user’s friend list alphabetically, and an Unsorted List to store Blocked Users.
* **Dynamic Memory Allocation:** Strictly manage `new` and `delete` in your constructors/destructors to prevent memory leaks when users delete their accounts.



**Member 3: The Algorithm Architect (Traversal & Discovery)**

* **Role:** You handle the complex math and discovery features that make the network smart.
* **Features:** Friend Suggestions (Friends of Friends), Mutual Friends, Degrees of Separation, Community Detection.
* **Required DSA Concepts:**
* **Queue (Linked List based):** Build a queue to run **BFS**. Use this for Friend Suggestions and finding the shortest connection path between two strangers.
* **Stack (Array based) & Recursion:** Implement **DFS** to traverse the entire network to map out "Communities" (isolated clusters of friends). Do this using both the iterative stack method and the recursive method.



**Member 4: Content & Feed Engine**

* **Role:** You manage what users actually *see* when they log in to the network.
* **Features:** Chronological News Feed, Trending/Viral Feed, Post Creation.
* **Required DSA Concepts:**
* **Stack (Linked List based):** Implement the "Chronological Feed". Every new post is pushed to the top, so the user sees the most recent content first (LIFO).
* **Priority Queue:** Build a "Trending Feed" where posts are popped out based on engagement (likes/comments) rather than time.



**Member 5: Real-Time Interaction & System Integrator**

* **Role:** You handle the user-to-user interactions and build the central Command Line Interface (CLI) that brings everyone's code together.
* **Features:** Friend Request Inbox, Notifications, "Undo" button, Main Menu UI.
* **Required DSA Concepts:**
* **Queue (Array based):** Create a "Pending Requests & Notifications" inbox. First friend request sent is the first one you see (FIFO).
* **Stack (Array based):** Create an "Action History" stack for an **Undo System** (e.g., undoing an accidental friend request or a deleted post).
* **System Integration:** Write the `main.cpp` switch-case loop that elegantly connects Member 1's BST, Member 2's Graph, Member 3's Algorithms, and Member 4's Feeds.

* what we used from the syllabus for what features:

* **Classes, Objects & Operator Overloading:** We created a `User` class and overloaded the `<`, `>`, and `==` operators so we could compare user IDs.
* **Template Class & Dynamic Memory:** We built the `Graph` as a template class (`template <class T>`) so it could hold our `User` objects, carefully using `new` and `delete` to prevent memory leaks.
* **Graph & Linked List:** The social network uses an Adjacency List Graph, where each array index holds a custom **Linked List** of friends.
* **BST (Binary Search Tree):** Instead of using a basic array, we stored all registered users in a BST for faster searching during login.
* **Queue (Array & Linked List based):** We built a **Linked List Queue** for the BFS algorithm (Friend Suggestions) and an **Array Queue** for the Friend Request Inbox.
* **Stack (Array & Linked List based):** We used a **Linked List Stack** for the Chronological Feed (most recent post on top) and an **Array Stack** for the Undo Action feature.
* **Recursion:** We used **Recursion** for the DFS traversal to find isolated friend groups.
* **Priority Queue:** We used this strictly for a "Trending Feed" to sort posts by the highest number of likes.
* **Sorted & Unsorted Lists (Array/LL):** We used a **Sorted List** to display a user's friend list alphabetically, and an **Unsorted List** to keep track of blocked accounts.

### 🚨What to AVOID in our project:
1. **NO Standard Template Library (STL):** Do not `#include <vector>`, `<stack>`, `<queue>`, `<list>`, or `<map>`. You **must** build all Stacks, Queues, and Lists from scratch using pointers and arrays just like you did in the lab assignments.
2. **NO Advanced Trees:** Do not use AVL Trees or Red-Black Trees. Stick strictly to a standard Binary Search Tree (BST).
3. **NO Hashing/Hash Maps:** Even though Hash Maps are great for storing users, it was not taught in our lab. Use BST instead.
4. **NO Shortest Path Algorithms:** Do not use Dijkstra's Algorithm because it was not taught in class. To find the "degrees of separation," just use standard **BFS**, which naturally finds the shortest path in an unweighted graph.

