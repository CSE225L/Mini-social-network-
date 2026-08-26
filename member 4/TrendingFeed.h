#ifndef TRENDINGFEED_H_INCLUDED
#define TRENDINGFEED_H_INCLUDED
#include <iostream>
#include "post.h"
using namespace std;

const int MAX_TRENDING = 200;

class TrendingFeed
{
private:
    Post posts[MAX_TRENDING];
    int count;

    void resort()
    {
        for (int i = 1; i < count; i++)
        {
            Post key = posts[i];
            int j = i - 1;
            while (j >= 0 && posts[j] < key)
            {
                posts[j + 1] = posts[j];
                j--;
            }
            posts[j + 1] = key;
        }
    }

public:
    TrendingFeed() : count(0) {}

    void addOrUpdatePost(const Post& p)
    {
        for (int i = 0; i < count; i++)
        {
            if (posts[i] == p)
            {
                posts[i] = p;
                resort();
                return;
            }
        }
        if (count >= MAX_TRENDING) return;
        posts[count] = p;
        count++;
        resort();
    }

    Post popTopTrending()
    {
        Post top = posts[0];
        for (int i = 0; i < count - 1; i++) posts[i] = posts[i + 1];
        count--;
        return top;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    void showTopN(int n) const
    {
        cout << "\n        TRENDING FEED (Top " << n << " by Engagement)       \n";
        int limit = (n < count) ? n : count;
        if (limit == 0)
        {
            cout << "  (No trending posts yet)\n";
            return;
        }
        for (int i = 0; i < limit; i++) posts[i].display();
    }
};


#endif // TRENDINGFEED_H_INCLUDED
