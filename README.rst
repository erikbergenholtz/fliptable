=====
fliptable, v0.1.0
=====

Version
=====
0.1.0

Authors
=====
``fliptable`` is written by Erik Bergenholtz

License
=====
GPLv3, See `LICENSE`_.


About
=====
``fliptable`` is a piece of software designed to do one thing: Show your rage
by animating a table-flip through UTF-8.

Why?
-----
We've all been there; hour after hour of scratching your head over a
particularily nasty piece of code, only to have it blow up in your face, forcing
you to make a hard reset of the git repository. This nifty program helps you
share your rage with your coworkers, even while you're away to angrily grab a
cup of very, very black coffee.

Usage
-----
``fliptable`` only takes optional arguments, which are listed below. If the
arguments are omitted the program will choose which figures will flip tables
until the end of time for you.

+------------+----------------------------------------------------------+
| ``-r NUM`` | Pick the face of the figure flipping the table. NUM is   |
|            | the number in the table under "Available faces" below.   |
+------------+----------------------------------------------------------+
| ``-c NUM`` | Pick the face of the figure preparing to flip the table. |
|            | NUM is the number in the table under "Available faces"   |
|            | below.                                                   |
+------------+----------------------------------------------------------+
| ``-l``     | List available faces                                     |
+------------+----------------------------------------------------------+

Available faces
+++++

+---+--------+
| 1 |  ͡° ͜ʖ ͡° |
+---+--------+
| 2 |  ͡☉ ͜ʖ ͡☉ |
+---+--------+
| 3 | °□°    |
+---+--------+
| 4 | ✧Д✧    |
+---+--------+
| 5 | ◉Д◉    |
+---+--------+
| 6 | °益°   |
+---+--------+

Example usage
+++++
``fliptable -r 4 -c 2`` will result in the calm face "(  ͡☉ ͜ʖ ͡☉)" and raging face
"(ノ✧Д✧)ノ".






:: _`LICENSE` : https://github.com/Psyberion/fliptable/blob/master/LICENSE
