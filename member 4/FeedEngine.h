#ifndef FEEDENGINE_H_INCLUDED
#define FEEDENGINE_H_INCLUDED
#include <iostream>
#include "post.h"
#include "ChronologicalFeed.h"
#include "TrendingFeed.h"
#include "graph.h"
using namespace std;

const int MAX_ALL_POSTS = 1000;

class FeedEngine
{
private:
    ChronologicalFeed chronoFeed;
    TrendingFeed trending;
    Post allPosts[MAX_ALL_POSTS];
    int totalPosts;
    int nextPostID;

public:
    FeedEngine() : totalPosts(0), nextPostID(1) {}

    void createPost(int authorID, string authorName, string content, string timestamp)
    {
        Post p(nextPostID++, authorID, authorName, content, timestamp);
        addToAllFeeds(p);
    }

    void createPost(const User& author, string content, string timestamp)
    {
        Post p(nextPostID++, author, content, timestamp);
        addToAllFeeds(p);
    }

    void likePost(int postID)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if (allPosts[i].getPostID() == postID)
            {
                allPosts[i].addLike();
                trending.addOrUpdatePost(allPosts[i]);
                return;
            }
        }
        cout << "  (Post #" << postID << " not found.)\n";
    }

    void commentOnPost(int postID)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if (allPosts[i].getPostID() == postID)
            {
                allPosts[i].addComment();
                trending.addOrUpdatePost(allPosts[i]);
                return;
            }
        }
        cout << "  (Post #" << postID << " not found.)\n";
    }

    void showChronological() const
    {
        chronoFeed.showFeed();
    }
    void showTrending(int topN = 5) const
    {
        trending.showTopN(topN);
    }


    void showFriendsFeed(int viewerID) const
    {
        int friendCount = 0;
        int* friendIDs = infoNeededFromMember2_getFriendIDs(viewerID, friendCount);

        cout << "\n===== FRIENDS-ONLY FEED (viewer #" << viewerID << ") =====\n";
        bool found = false;
        for (int i = 0; i < totalPosts; i++)
        {
            for (int f = 0; f < friendCount; f++)
            {
                if (allPosts[i].getAuthorID() == friendIDs[f] &&
                        !infoNeededFromMember2_isBlocked(viewerID, allPosts[i].getAuthorID()))
                {
                    allPosts[i].display();
                    found = true;
                }
            }
        }
        if (!found)
        {
            cout << "  (No posts from friends yet - using mock friend IDs while\n";
            cout << "   waiting on Member 2's real Graph: 101, 102, 103)\n";
        }
        delete[] friendIDs;
    }

    int getTotalPosts() const
    {
        return totalPosts;
    }

private:
    void addToAllFeeds(const Post& p)
    {
        chronoFeed.newPost(p);
        trending.addOrUpdatePost(p);
        if (totalPosts < MAX_ALL_POSTS)
        {
            allPosts[totalPosts++] = p;
        }
        cout << "Post #" << p.getPostID() << " created by " << p.getAuthorName() << ".\n";
    }
};



#endif // FEEDENGINE_H_INCLUDED
