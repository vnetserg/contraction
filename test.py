#!/usr/bin/env python3

'''
    This script tests the correctness of the algorithm implementation
    using the technique called 'stress testing'. It pseudorandomly generates
    test cases for the algorithm, and then uses 'networkx' Python library
    to compute the right answer. Then it calls the app to get it's answers
    and checks if they match.
'''

import sys
import math
import random
import argparse
import subprocess

import networkx
from networkx import dijkstra_path_length
from networkx.generators.random_graphs import gnm_random_graph


AUTO_MAX_EDGES = 1000
AUTO_MAX_VERTICES = 250
APP_TIMEOUT_SEC = 5
MAX_WEIGHT = 20000


# General ase exception
class Error(Exception): pass

# Exception used by call_app when call timeout is expired
class TimeoutExpiredError(Error): pass


def generate_graph(n_vert, n_edges):
    '''
        Generate graph that consists of `n_vert` (ing) vertices
        and `n_edges` (int) edges. Return `networkx.classes.graph.Graph`.
    '''
    graph = gnm_random_graph(n_vert, n_edges, random.random(), True)
    for v1, v2 in graph.edges():
        w = random.randrange(1, MAX_WEIGHT)
        graph.edge[v1][v2]["weight"] = w
    return graph


def shortest_path(graph, src, dst):
    '''
        Return shortest path length on `graph` (`networkx.classes.graph.Graph`)
        from `src` (int) to `dst` (int). If path does not exist, return -1.
    '''
    try:
        return dijkstra_path_length(graph, src, dst)
    except networkx.exception.NetworkXNoPath:
        return -1


def call_app(app, graph, queries):
    '''
        Call `app` (path string), feeding `graph` (`networkx.classes.graph.Graph`)
        to it's stdout, then `queries` (tuples of source and destination
        vertex indices). Return list of ints, where i-th element denotes
        the length of the shortest path corresponding to queries[i].
    '''
    stdin = make_stdin(graph, queries)

    try:
        pipe = subprocess.Popen([app], stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            stdin=subprocess.PIPE)
    except FileNotFoundError:
        raise Error(exc.strerror)

    try:
        res, err = pipe.communicate(stdin.encode("ascii"), timeout=APP_TIMEOUT_SEC)
    except subprocess.TimeoutExpired:
        raise TimeoutExpiredError("timeout expired while calling the app")
    else:
        lines = res.decode("ascii").split()
        return [int(x) for x in lines[1:]]


def make_stdin(graph, queries):
    '''
        Transform `graph` (`networkx.classes.graph.Graph`) and `queries` (tuples
        of source and destination vertex indices) into a string representation
        suitable for the app stdin.
    '''
    return "p sp {n_vert} {n_edges}\n" \
        "{edges}\n" \
        "{n_queries}\n" \
        "{queries}\n" \
        .format(
            n_vert=len(graph.nodes()), n_edges=len(graph.edges()),
            edges="\n".join("a {} {} {}".format(v1+1, v2+1, graph.edge[v1][v2]["weight"])
                            for v1, v2 in graph.edges()),
            n_queries=len(queries),
            queries="\n".join("{} {}".format(q[0]+1, q[1]+1) for q in queries)
        )


def make_report(graph, queries, true_answers, my_answers=None):
    '''
        Make a human-readable report on the test case. Parameters:

        + `graph` — `networkx.classes.graph.Graph`;
        + `queries` — tuples of source and destination vertex indices;
        + `true_answers` — a list of ints, where i-th int denotes the shortest
                path length corresponding to queries[i];
        + `my_answers` — same as `true_answers`, but returned from the app.

        Return: string.
    '''
    s = "STDIN:\n{}EXPECTED OUTPUT:\n{}".format(
            make_stdin(graph, queries), "\n".join(str(x) for x in true_answers))
    if my_answers is not None:
        s += "\nREAL OUTPUT:\n{}".format("\n".join(str(x) for x in my_answers))
    return s


def main():
    ''' Entry point of the application. '''

    parser = argparse.ArgumentParser()
    parser.add_argument("app", help="path to the application")
    parser.add_argument("-t", "--tests", type=int, default=100,
        help="number of tests to perform")
    parser.add_argument("-q", "--queries", type=int, default=10,
        help="queries per test")
    parser.add_argument("-v", "--vertices", type=int, help="number of graph vertices")
    parser.add_argument("-e", "--edges", type=int, help="number of edges")
    parser.add_argument("-r", "--random", type=int, default=42,
        help="PRNG seed")
    args = parser.parse_args()

    random.seed(args.random)
    for i in range(args.tests):
        n_vert = args.vertices if args.vertices is not None \
                else random.randrange(1, AUTO_MAX_VERTICES)
        n_edges = args.edges if args.edges is not None \
                else random.randrange(min(AUTO_MAX_EDGES, (n_vert*(n_vert-1))//2)+1)
        graph = generate_graph(n_vert, n_edges)
        queries = [(random.randrange(n_vert), random.randrange(n_vert))
                   for _ in range(args.queries)]
        true_answers = [shortest_path(graph, src, dst) for src, dst in queries]

        try:
            my_answers = call_app(args.app, graph, queries)
        except TimeoutExpiredError as exc:
            print("Timeout expired on test #{}".format(i+1))
            print(make_report(graph, queries, true_answers))
            sys.exit(1)
        except Error as exc:
            print("Failed to call app: {}".format(exc))
            sys.exit(2)

        if true_answers == my_answers:
            print("Passed tests: {}/{}".format(i+1, args.tests), end="\r")
        else:
            print("Failed test #{}".format(i+1))
            print(make_report(graph, queries, true_answers, my_answers))
            sys.exit(3)

    print("")
    sys.exit(0)


if __name__ == "__main__":
    main()
