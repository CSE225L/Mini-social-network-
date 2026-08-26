#include <iostream>
#include <string>

#include "User.h"
#include "BST.h"
#include "Graph.h"
#include "SortedList.h"
#include "UnsortedList.h"
#include "Member3Algorithms.h"
#include "FeedEngine.h"
#include "InboxQueue.h"
#include "UndoStack.h"

using namespace std;

void printMenu()
{
    cout << endl;
    cout << "========== Mini Social Network ==========" << endl;
    cout << "1. Register user" << endl;
    cout << "2. Login" << endl;
    cout << "3. Logout" << endl;
    cout << "4. Search user (BST)" << endl;
    cout << "5. Display all users (BST)" << endl;
    cout << "6. Send friend request" << endl;
    cout << "7. View inbox" << endl;
    cout << "8. Accept friend request" << endl;
    cout << "9. Show friends (alphabetical)" << endl;
    cout << "10. Block user" << endl;
    cout << "11. Show blocked users" << endl;
    cout << "12. Friend suggestions (BFS)" << endl;
    cout << "13. Mutual friends" << endl;
    cout << "14. Degrees of separation (BFS)" << endl;
    cout << "15. Find communities (DFS)" << endl;
    cout << "16. Create post" << endl;
    cout << "17. Delete post" << endl;
    cout << "18. Like post" << endl;
    cout << "19. Comment on post" << endl;
    cout << "20. Chronological feed" << endl;
    cout << "21. Trending feed" << endl;
    cout << "22. Friends feed" << endl;
    cout << "23. Undo last action" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
}

int main()
{
    BST userDB;
    Graph<User> network(MAX_USERS);
    UnsortedList blocked[MAX_USERS];
    Member3Algorithms algo;
    FeedEngine feed;
    InboxQueue inbox;
    UndoStack history;

    int currentID = -1;
    int choice = -1;

    while (choice != 0)
    {
        if (currentID != -1)
        {
            int idx = network.FindIndexByID(currentID);
            if (idx != -1)
            {
                User me = network.GetUser(idx);
                cout << endl << "Logged in as: " << me.getName()
                     << " (ID " << me.getID() << ")" << endl;
            }
        }
        else
        {
            cout << endl << "Not logged in." << endl;
        }

        printMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input." << endl;
            choice = -1;
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
        {
            int id;
            string name;
            char vipChoice;
            cout << "Enter new user ID: ";
            cin >> id;
            cin.ignore(1000, '\n');
            cout << "Enter name: ";
            getline(cin, name);
            cout << "VIP user? (y/n): ";
            cin >> vipChoice;

            if (userDB.searchByID(id) != NULL)
            {
                cout << "That ID is already registered." << endl;
                break;
            }

            bool vip = (vipChoice == 'y' || vipChoice == 'Y');
            User u(id, name, vip);
            userDB.insert(u);
            network.AddUser(u);
            cout << "User registered." << endl;
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter user ID: ";
            cin >> id;
            DBNode* found = userDB.searchByID(id);
            if (found == NULL)
            {
                cout << "Login failed. User not found." << endl;
            }
            else
            {
                currentID = id;
                cout << "Welcome, " << found->info.getName() << "!" << endl;
            }
            break;
        }
        case 3:
        {
            currentID = -1;
            cout << "Logged out." << endl;
            break;
        }
        case 4:
        {
            int id;
            cout << "Enter user ID to search: ";
            cin >> id;
            DBNode* found = userDB.searchByID(id);
            if (found == NULL)
            {
                cout << "User not found." << endl;
            }
            else
            {
                found->info.Print();
            }
            break;
        }
        case 5:
        {
            cout << endl << "Registered users:" << endl;
            userDB.displayAll();
            break;
        }
        case 6:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int toID;
            cout << "Enter ID of user to request: ";
            cin >> toID;
            if (toID == currentID)
            {
                cout << "You cannot send a request to yourself." << endl;
                break;
            }
            if (userDB.searchByID(toID) == NULL)
            {
                cout << "User not found." << endl;
                break;
            }
            int fromIdx = network.FindIndexByID(currentID);
            int toIdx = network.FindIndexByID(toID);
            if (blocked[fromIdx].ContainsID(toID) || blocked[toIdx].ContainsID(currentID))
            {
                cout << "Cannot send request. A block is in place." << endl;
                break;
            }
            if (network.AreFriends(fromIdx, toIdx))
            {
                cout << "You are already friends." << endl;
                break;
            }
            if (inbox.hasPendingRequest(currentID, toID))
            {
                cout << "Request already pending." << endl;
                break;
            }

            Notification req;
            req.fromID = currentID;
            req.toID = toID;
            req.type = 1;
            req.text = "Friend request";
            inbox.enqueue(req);

            Notification note;
            note.fromID = currentID;
            note.toID = toID;
            note.type = 2;
            note.text = "You received a friend request.";
            inbox.enqueue(note);

            Action a;
            a.type = ACTION_SEND_REQUEST;
            a.userA = currentID;
            a.userB = toID;
            history.push(a);

            cout << "Friend request sent." << endl;
            break;
        }
        case 7:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            inbox.displayForUser(currentID);
            break;
        }
        case 8:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int fromID;
            cout << "Enter ID of the sender to accept: ";
            cin >> fromID;
            if (!inbox.hasPendingRequest(fromID, currentID))
            {
                cout << "No pending request from that user." << endl;
                break;
            }

            int aIdx = network.FindIndexByID(fromID);
            int bIdx = network.FindIndexByID(currentID);
            network.AddFriend(aIdx, bIdx);
            inbox.removeRequest(fromID, currentID);

            Notification note;
            note.fromID = currentID;
            note.toID = fromID;
            note.type = 2;
            note.text = "Your friend request was accepted.";
            inbox.enqueue(note);

            Action a;
            a.type = ACTION_ACCEPT_FRIEND;
            a.userA = fromID;
            a.userB = currentID;
            history.push(a);

            cout << "Friend request accepted." << endl;
            break;
        }
        case 9:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int idx = network.FindIndexByID(currentID);
            User list[MAX_USERS];
            int n = 0;
            int ids[MAX_USERS];
            network.FillFriendIDs(idx, ids, n);
            SortedList alpha;
            for (int i = 0; i < n; i++)
            {
                int fIdx = network.FindIndexByID(ids[i]);
                if (fIdx != -1)
                {
                    alpha.Insert(network.GetUser(fIdx));
                }
            }
            cout << endl << "Alphabetical friend list:" << endl;
            alpha.Print();
            break;
        }
        case 10:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int blockID;
            cout << "Enter ID to block: ";
            cin >> blockID;
            DBNode* found = userDB.searchByID(blockID);
            if (found == NULL)
            {
                cout << "User not found." << endl;
                break;
            }
            int idx = network.FindIndexByID(currentID);
            int other = network.FindIndexByID(blockID);
            blocked[idx].Insert(found->info);
            if (other != -1)
            {
                network.RemoveFriend(idx, other);
            }
            Action a;
            a.type = ACTION_BLOCK_USER;
            a.userA = currentID;
            a.userB = blockID;
            history.push(a);
            cout << "User blocked." << endl;
            break;
        }
        case 11:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int idx = network.FindIndexByID(currentID);
            cout << endl << "Blocked users:" << endl;
            blocked[idx].Print();
            break;
        }
        case 12:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int matrix[MAX_USERS][MAX_USERS];
            network.BuildAdjMatrix(matrix);
            int n = network.GetUserCount();
            int start = network.FindIndexByID(currentID);
            algo.friendSuggestions(matrix, n, start);
            cout << "(Numbers shown are graph indexes. Use Display all users to map IDs.)" << endl;
            cout << "Index mapping:" << endl;
            for (int i = 0; i < n; i++)
            {
                User u = network.GetUser(i);
                cout << "  Index " << i << " -> ID " << u.getID() << " " << u.getName() << endl;
            }
            break;
        }
        case 13:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int otherID;
            cout << "Enter other user ID: ";
            cin >> otherID;
            int aIdx = network.FindIndexByID(currentID);
            int bIdx = network.FindIndexByID(otherID);
            if (bIdx == -1)
            {
                cout << "User not found." << endl;
                break;
            }
            int matrix[MAX_USERS][MAX_USERS];
            network.BuildAdjMatrix(matrix);
            algo.mutualFriends(matrix, network.GetUserCount(), aIdx, bIdx);
            break;
        }
        case 14:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int otherID;
            cout << "Enter target user ID: ";
            cin >> otherID;
            int aIdx = network.FindIndexByID(currentID);
            int bIdx = network.FindIndexByID(otherID);
            if (bIdx == -1)
            {
                cout << "User not found." << endl;
                break;
            }
            int matrix[MAX_USERS][MAX_USERS];
            network.BuildAdjMatrix(matrix);
            int dist = algo.degreesOfSeparation(matrix, network.GetUserCount(), aIdx, bIdx);
            if (dist == -1)
            {
                cout << "No path between these users." << endl;
            }
            else
            {
                cout << "Degrees of separation: " << dist << endl;
            }
            break;
        }
        case 15:
        {
            int n = network.GetUserCount();
            if (n == 0)
            {
                cout << "No users in the network." << endl;
                break;
            }
            int matrix[MAX_USERS][MAX_USERS];
            network.BuildAdjMatrix(matrix);
            algo.findCommunities(matrix, n);
            algo.DFSIterative(matrix, n, 0);
            break;
        }
        case 16:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            string content;
            string timeStamp;
            cout << "Enter post text: ";
            getline(cin, content);
            cout << "Enter timestamp: ";
            getline(cin, timeStamp);
            int idx = network.FindIndexByID(currentID);
            User me = network.GetUser(idx);
            int postID = feed.createPost(me.getID(), me.getName(), content, timeStamp);

            Action a;
            a.type = ACTION_CREATE_POST;
            a.userA = currentID;
            a.userB = postID;
            history.push(a);
            break;
        }
        case 17:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int postID;
            cout << "Enter post ID to delete: ";
            cin >> postID;
            Post saved;
            if (!feed.getPostByID(postID, saved))
            {
                cout << "Post not found." << endl;
                break;
            }
            if (saved.getAuthorID() != currentID)
            {
                cout << "You can only delete your own posts." << endl;
                break;
            }
            Post removed;
            feed.deletePost(postID, removed);
            Action a;
            a.type = ACTION_DELETE_POST;
            a.userA = currentID;
            a.userB = postID;
            a.savedPost = removed;
            history.push(a);
            break;
        }
        case 18:
        {
            int postID;
            cout << "Enter post ID to like: ";
            cin >> postID;
            feed.likePost(postID);
            break;
        }
        case 19:
        {
            int postID;
            cout << "Enter post ID to comment on: ";
            cin >> postID;
            feed.commentOnPost(postID);
            break;
        }
        case 20:
        {
            feed.showChronological();
            break;
        }
        case 21:
        {
            int n;
            cout << "How many trending posts to show? ";
            cin >> n;
            feed.showTrending(n);
            break;
        }
        case 22:
        {
            if (currentID == -1)
            {
                cout << "Login first." << endl;
                break;
            }
            int idx = network.FindIndexByID(currentID);
            int ids[MAX_USERS];
            int n = 0;
            network.FillFriendIDs(idx, ids, n);
            feed.showFriendsFeed(ids, n);
            break;
        }
        case 23:
        {
            if (history.isEmpty())
            {
                cout << "Nothing to undo." << endl;
                break;
            }
            Action a = history.pop();
            if (a.type == ACTION_SEND_REQUEST)
            {
                inbox.removeRequest(a.userA, a.userB);
                cout << "Undid friend request." << endl;
            }
            else if (a.type == ACTION_ACCEPT_FRIEND)
            {
                int aIdx = network.FindIndexByID(a.userA);
                int bIdx = network.FindIndexByID(a.userB);
                network.RemoveFriend(aIdx, bIdx);
                cout << "Undid accept friend." << endl;
            }
            else if (a.type == ACTION_CREATE_POST)
            {
                Post dummy;
                feed.deletePost(a.userB, dummy);
                cout << "Undid create post." << endl;
            }
            else if (a.type == ACTION_DELETE_POST)
            {
                feed.restorePost(a.savedPost);
                cout << "Undid delete post." << endl;
            }
            else if (a.type == ACTION_BLOCK_USER)
            {
                int idx = network.FindIndexByID(a.userA);
                blocked[idx].RemoveID(a.userB);
                cout << "Undid block user." << endl;
            }
            break;
        }
        case 0:
        {
            cout << "Goodbye." << endl;
            break;
        }
        default:
        {
            cout << "Unknown choice." << endl;
            break;
        }
        }
    }

    return 0;
}
