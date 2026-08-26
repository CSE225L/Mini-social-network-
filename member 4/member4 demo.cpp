
#include <iostream>
#include "FeedEngine.h"
using namespace std;

int main()
{
    FeedEngine feed;

    cout << "--- Creating posts ---\n";
    feed.createPost(101, "Sayma", "Just joined the network!", "2026-08-26 09:00");
    feed.createPost(102, "Sharif", "Loving this project so far.", "2026-08-26 09:15");
    feed.createPost(101, "Sazzad", "Anyone up for a study group?", "2026-08-26 10:00");

    cout << "\n--- Simulating engagement ---\n";
    feed.likePost(1);
    feed.likePost(1);
    feed.commentOnPost(1);
    feed.likePost(3);

    feed.showChronological();
    feed.showTrending(3);
    feed.showFriendsFeed(999);

    cout << "\nTotal posts created: " << feed.getTotalPosts() << "\n";
    return 0;
}
