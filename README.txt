Contributions:
Brandon - I did the heuristic functions. I read different strategy websites and based
my final heuristic structure off of two different papers. I played around with the weights
that were in each heuristic along with the static table of weights. I also adjusted the 
importance of each category.

Improvements
We started with a few if statements for our heuristic that solely depended on a greedy strategy 
that tried to maximize short term gain. We then switched over to a table ot static heuristics
still based on the weighted count for a greedy strategy. Then we realized that the greedy 
strategy doesn't work for Othello and so we implemented a structured heuristic that applied
different weights to four different categories, being corners, mobility, stability, and the weighted
count. This drastically improved our win percentage against ConstantTimePlayer.