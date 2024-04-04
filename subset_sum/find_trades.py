"""
This script analyzes a list of trades to find combinations that add up to a target quantity.

Usage:
    python script.py filename target_quantity

    filename: Path to the file containing trades data.
    target_quantity: The desired total quantity of trades to be found.

The script reads trades data from the specified file, where each line represents a trade record in the format:
    date time price currency quantity value venue instrument

Trades are represented as namedtuples with the following fields:
    - date: The date of the trade.
    - time: The time of the trade.
    - price: The price of the trade.
    - currency: The currency of the trade.
    - quantity: The quantity of the trade.
    - value: The value of the trade.
    - venue: The venue of the trade.
    - instrument: The instrument of the trade.

The script then finds combinations of trades that add up to the target quantity using dynamic programming.

Example:
    python script.py trades.txt 1000

This will analyze the trades data in 'trades.txt' and find combinations of trades that add up to 1000 in quantity.
"""


import argparse
from collections import namedtuple


class Trade(
    namedtuple(
        "Trade",
        [
            "date",
            "time",
            "price",
            "currency",
            "quantity",
            "value",
            "venue",
            "instrument",
        ],
        defaults=(None,) * 8,
    )
):
    def __repr__(self):
        fields = []
        for field, value in zip(self._fields, self):
            if value is not None:
                s = "'" if isinstance(value, str) else ""
                fields.append(f"{field}={s}{value}{s}")
        return f"Trade({', '.join(fields)})"


def parse_trade_line(line):
    """
    Parse a line from the trade file and return a Trade namedtuple.

    Args:
        line (str): A line from the trade file.

    Returns:
        Trade: A namedtuple representing the trade.

    For example:
    >>> parse_trade_line("03.04.24 11:19:12 117.00 GBX 881 1,030.77 AT XLON")
    Trade(date='03.04.24', time='11:19:12', price=117.0, currency='GBX', quantity=881, value=1030.77, venue='AT', instrument='XLON')
    >>>

    """
    parts = line.split()
    date = parts[0]
    time = parts[1]
    price = float(parts[2])
    currency = parts[3]
    quantity = int(parts[4].replace(",", ""))
    value = float(parts[5].replace(",", ""))
    venue = parts[6]
    instrument = parts[7]
    return Trade(date, time, price, currency, quantity, value, venue, instrument)


def read_trades_from_file(filename):
    """
    Read trades from a file and return a list of Trade namedtuples.

    Args:
        filename (str): The path to the file containing trades.

    Returns:
        list: A list of Trade namedtuples.

    """
    trades = []
    with open(filename, "r") as file:
        for line in file:
            trades.append(parse_trade_line(line))
    return trades


def find_trades(trades, target_quantity):
    """
    Find trades that add up to a target quantity.

    Args:
        trades (list): A list of Trade namedtuples.
        target_quantity (int): The target total quantity of trades.

    Returns:
        list or None: A list of Trade namedtuples that add up to the target quantity, or None if no such combination exists.

    >>> trades = [Trade(quantity=586), Trade(quantity=881), Trade(quantity=614), Trade(quantity=458), Trade(quantity=635)]
    >>> find_trades(trades, 1200)
    [Trade(quantity=586), Trade(quantity=614)]
    >>>

    """

    # Essentially the Subset sum problem. Use dynamic programming to solve.

    n = len(trades)
    dp = [[None] * (target_quantity + 1) for _ in range(n + 1)]

    for i in range(n + 1):
        dp[i][0] = []

    for i, trade in enumerate(trades):
        for j in range(1, target_quantity + 1):
            if trade.quantity <= j:
                if dp[i][j - trade.quantity] is not None:
                    dp[i + 1][j] = dp[i][j - trade.quantity] + [i]
                elif dp[i][j] is not None:
                    dp[i + 1][j] = dp[i][j]
            else:
                if dp[i][j] is not None:
                    dp[i + 1][j] = dp[i][j]

    if dp[n][target_quantity] is None:
        return None

    result = []
    for idx in dp[n][target_quantity]:
        result.append(trades[idx])
    return result


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Find trades that add up to a target quantity"
    )
    parser.add_argument("filename", type=str, help="Path to the file containing trades")
    parser.add_argument(
        "target_quantity", type=int, help="Target total quantity of trades"
    )
    args = parser.parse_args()

    trades = read_trades_from_file(args.filename)
    result = find_trades(trades, args.target_quantity)
    if result:
        print("Trades found that add up to the target quantity:")
        for trade in result:
            print(trade)
    else:
        print("No trades found that add up to the target quantity.")
