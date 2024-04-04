Summing exchange trades to target
=================================

I noticed that when I placed a sale of company shares, which I then rebought
back into an ISA so that my future gains would be shielded from tax, my
transaction quantity never appeared in the timeline of trades occuring on the
London Stock Exchange.

Yet, I wanted to confirm, in some fashion, that my transaction was in there
somewhere. Of course what happens on an exchange is larger transactions get
broken down into smaller pieces. As a consumer to the market, and not a broker
or any other entity, this is actually pretty annoying because it need not
have been broken down at all since I placed my buy and sell order at the same
time!  Maybe if both dealing account and ISA account are with the same broker,
which in my case they weren't, this so called "Bed and ISA" process can be
performed better. Still it is what it is.

Anyway, my transaction had clearly been broken down. So to try and find these
smaller pieces I thought, let's take some trade history data from the time
window over which my sale was filled. I saw from my notifications it took about
10 minutes so it was simple enough to pull out some record lines from that
period.

Next I created a program that will parse this file and find the trades that add
up to the total quantity of my sale. It took a little bit of persuasion to get
the AI to write the code just how I wanted it. I had to tell it explicitly to
use dynamic programming to get the answer because it did something too simple
to start with that wouldn't have worked. And it didn't do it with idiomatic
python. Since I like tests I also asked it to add some, but I then had modify
the numbers myself for correct doctest cases. I got there in the end. Despite
the tidying and direction I had to give it is still so much quicker to generate
such routine code for well-known problems, and then fix it up, than to
synthesise it yourself from scratch.

Anyway, I was able to find the trades that were probably the ones involved in
my sale. So happy to have seen I made a tiny mark somewhere in the history of
the exchange, and it was fun anyway to put this together.

This problem felt a bit knapsack-problem-like, and indeed it is. The [Subset
sum problem](https://en.wikipedia.org/wiki/Subset_sum_problem) which this is,
is a special case of the Knapsack problem.

