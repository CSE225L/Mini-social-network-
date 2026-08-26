#ifndef FEEDENGINE_H_INCLUDED
#define FEEDENGINE_H_INCLUDED

#include <iostream>
#include "Post.h"
#include "ChronologicalFeed.h"
#include "TrendingFeed.h"
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

    void rebuildFeeds()
    {
        chronoFeed.clear();
        trending.clear();
        for (int i = 0; i < totalPosts; i++)
        {
            chronoFeed.newPost(allPosts[i]);
            trending.addOrUpdatePost(allPosts[i]);
        }
    }

public:
    FeedEngine()
    {
        totalPosts = 0;
        nextPostID = 1;
    }

    int createPost(int authorID, string authorName, string content, string timestamp)
    {
        Post p(nextPostID, authorID, authorName, content, timestamp);
        nextPostID++;
        if (totalPosts < MAX_ALL_POSTS)
        {
            allPosts[totalPosts] = p;
            totalPosts++;
        }
        chronoFeed.newPost(p);
        trending.addOrUpdatePost(p);
        cout << "Post #" << p.getPostID() << " created by " << p.getAuthorName() << "." << endl;
        return p.getPostID();
    }

    bool getPostByID(int postID, Post& out)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if (allPosts[i].getPostID() == postID)
            {
                out = allPosts[i];
                return true;
            }
        }
        return false;
    }

    void restorePost(Post p)
    {
        if (totalPosts >= MAX_ALL_POSTS)
        {
            return;
        }
        allPosts[totalPosts] = p;
        totalPosts++;
        rebuildFeeds();
        cout << "Post #" << p.getPostID() << " restored." << endl;
    }

    bool deletePost(int postID, Post& saved)
    {
        int index = -1;
        for (int i = 0; i < totalPosts; i++)
        {
            if (allPosts[i].getPostID() == postID)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            return false;
        }
        saved = allPosts[index];
        for (int i = index; i < totalPosts - 1; i++)
        {
            allPosts[i] = allPosts[i + 1];
        }
        totalPosts--;
        rebuildFeeds();
        cout << "Post #" << postID << " deleted." << endl;
        return true;
    }

    void likePost(int postID)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if (allPosts[i].getPostID() == postID)
            {
                allPosts[i].addLike();
                trending.addOrUpdatePost(allPosts[i]);
                rebuildFeeds();
                cout << "Liked post #" << postID << "." << endl;
                return;
            }
        }
        cout << "Post #" << postID << " not found." << endl;
    }

    void commentOnPost(int postID)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if (allPosts[i].getPostID() == postID)
            {
                allPosts[i].addComment();
                trending.addOrUpdatePost(allPosts[i]);
                rebuildFeeds();
                cout << "Commented on post #" << postID << "." << endl;
                return;
            }
        }
        cout << "Post #" << postID << " not found." << endl;
    }

    void showChronological() const
    {
        chronoFeed.showFeed();
    }

    void showTrending(int topN = 5) const
    {
        trending.showTopN(topN);
    }

    void showFriendsFeed(int friendIDs[], int friendCount)
    {
        cout << endl << "FRIENDS-ONLY FEED" << endl;
        bool found = false;
        for (int i = totalPosts - 1; i >= 0; i--)
        {
            for (int f = 0; f < friendCount; f++)
            {
                if (allPosts[i].getAuthorID() == friendIDs[f])
                {
                    allPosts[i].display();
                    found = true;
                }
            }
        }
        if (!found)
        {
            cout << "  (No posts from friends yet)" << endl;
        }
    }

    int getTotalPosts() const
    {
        return totalPosts;
    }
};

#endif
