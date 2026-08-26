#ifndef POST_H_INCLUDED
#define POST_H_INCLUDED

#include <iostream>
#include <string>
#include "User.h"
using namespace std;

class Post
{
private:
    int postID;
    int authorID;
    string authorName;
    string content;
    string timestamp;
    int likes;
    int comments;

public:
    Post(int id = 0, int authID = 0, string authName = "", string txt = "", string time = "")
    {
        postID = id;
        authorID = authID;
        authorName = authName;
        content = txt;
        timestamp = time;
        likes = 0;
        comments = 0;
    }

    Post(int id, const User& author, string txt, string time)
    {
        postID = id;
        authorID = author.getID();
        authorName = author.getName();
        content = txt;
        timestamp = time;
        likes = 0;
        comments = 0;
    }

    int getPostID() const
    {
        return postID;
    }

    int getAuthorID() const
    {
        return authorID;
    }

    string getAuthorName() const
    {
        return authorName;
    }

    string getContent() const
    {
        return content;
    }

    string getTimestamp() const
    {
        return timestamp;
    }

    int getLikes() const
    {
        return likes;
    }

    int getComments() const
    {
        return comments;
    }

    int getEngagement() const
    {
        return likes + comments;
    }

    void setLikes(int n)
    {
        likes = n;
    }

    void setComments(int n)
    {
        comments = n;
    }

    void addLike()
    {
        likes++;
    }

    void addComment()
    {
        comments++;
    }

    bool operator>(const Post& other) const
    {
        return getEngagement() > other.getEngagement();
    }

    bool operator<(const Post& other) const
    {
        return getEngagement() < other.getEngagement();
    }

    bool operator==(const Post& other) const
    {
        return postID == other.postID;
    }

    void display() const
    {
        cout << "  [Post #" << postID << "] " << authorName
             << " (" << timestamp << ")" << endl;
        cout << "    \"" << content << "\"" << endl;
        cout << "    Likes: " << likes << " | Comments: " << comments << endl;
    }
};

#endif
