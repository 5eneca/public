from collections import deque
import heapq

graph = {
    "Arad": {"Timisoara": 118, "Sibiu": 140,"Zerind": 75},
    "Zerind": {"Arad": 75, "Oradea": 71},
    "Oradea": {"Zerind": 71, "Sibiu": 151},
    "Timisoara": {"Arad": 118, "Lugoj": 111},
    "Lugoj": {"Timisoara": 111, "Mehadia":70},
    "Mehadia": {"Lugoj": 70, "Dobreta": 75},
    "Dobreta": {"Mehadia":75, "Craiova":120},
    "Craiova": {"Dobreta": 120, "RimnicuVilcea": 146, "Pitesi": 138},
    "RimnicuVilcea": {"Craiova": 146, "Pitesi": 97, "Sibiu":80},
    "Sibiu": {"Arad": 140, "Oradea":151, "RimnicuVilcea": 80, "Fagaras": 99},
    "Fagaras": {"Sibiu": 99, "Bucharest":211},
    "Pitesi": {"Bucharest": 101, "RimnicuVilcea": 97, "Craiova": 138},
    "Bucharest": {"Pitesi": 101, "Fagaras": 211, "Giurgiu": 90, "Urziceni": 85},
    "Giurgiu": {"Bucharest": 90},
    "Urziceni": {"Bucharest": 85, "Hirsova": 98, "Vaslui": 142},
    "Hirsova": {"Urziceni": 98, "Eforie": 86},
    "Eforie": {"Hirsova": 86},
    "Vaslui": {"Urziceni": 142, "Iasi": 92},
    "Iasi": {"Vaslui": 92, "Neamt": 87},
    "Neamt": {"Iasi": 87}
}

class GraphProblem:
    def __init__(self, initial, goal, graph):
        self.initial = initial
        self.goal = goal
        self.graph = graph


    def actions(self, state):
        return list(graph[state].keys())

    def result(self, state, action):
        return action

    def goalTest(self, state):
        return state == self.goal

    def pathCost(self, cost_so_far, fromState, action, toState):
        return cost_so_far + graph[fromState][toState]

class Node:
    def __init__(self, state, parent = None, 
                 action = None, path_cost = 0):        
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost

    def __lt__(self, node):
        return self.path_cost < node.path_cost      

    def childNode(self, graph_problem, action):        
        child_state = graph_problem.result(self.state, action)
        path_cost_to_childNode = graph_problem.pathCost(self.path_cost,
                                                        self.state, 
                                                        action,
                                                        child_state)        
        return Node(child_state, 
                    self, action, 
                    path_cost_to_childNode)

    def expand(self, graph_problem):
        return [self.childNode(graph_problem, action)
                for action in graph_problem.actions(self.state)]

def solution(node):
    lst = []
    while node:
        lst.append(node.state)
        #print(node.state)
        node = node.parent
    lst.reverse()
    return lst

def graphSearch(graph_problem, index = 0):
    frontier = []
    initialNode = Node(graph_problem.initial)
    frontier.append(initialNode)

    explored = set()

    while frontier:
        if len(frontier) == 0:
            return None

        node = frontier.pop(index)

        if graph_problem.goalTest(node.state):
            return graph_problem.actions(node.state)

        explored.add(node.state)

        for child in node.expand(graph_problem):
            if child not in frontier and                child.state not in explored:
                frontier.append(child)        

    return None

def BFS(graph_problem):
    node = Node(graph_problem.initial)
    if(graph_problem.goalTest(node.state)):
        return solution(node)
    frontier = deque([node])
    explored = set()
    while frontier:
        node = frontier.pop()
        explored.add(node.state)
        for action in graph_problem.actions(node.state):
            child = node.childNode(graph_problem, action)
            if child.state not in explored or child.state not in [n.state for n in frontier]:
                if graph_problem.goalTest(child.state):
                    return solution(child)
                frontier.append(child)
    return None

def UCS(problem):
    node = Node(problem.initial)
    frontier = []
    heapq.heappush(frontier, node)
    explored = set()
    while frontier:
        node = heapq.heappop(frontier)
        #print(node)
        if problem.goalTest(node.state):
            return solution(node)
        explored.add(node.state)
        for action in problem.actions(node.state):
            child = node.childNode(problem, action)
            if child.state not in explored or  child.state not in [n.state for n in frontier]:
                heapq.heappush(frontier, child)
            for i in range(len(frontier)):
                if frontier[i].state == child.state and frontier[i] > child: 
                    frontier[i] = child

def DLS(problem, limit = 4):
    return RDLS(Node(problem.initial), problem, limit)

def RDLS(node, problem, limit):
    if problem.goalTest(node.state):
        return solution(node)
    elif limit == 0:
        return -1
    else:
        cutoff_occurred = False
        for action in problem.actions(node.state):
            child = node.childNode(problem, action)
            result = RDLS(child, problem, limit - 1)
            if result == -1:
                cutoff_occurred = True
            elif result != None:
                return result
        if cutoff_occurred:
            return -1
        else:
            return None

def IDLS(problem):
    depth = 0
    while True:
        result = DLS(problem, depth)
        if result != -1:
            return result
        depth += 1

initial = 'Arad'
goal = 'Bucharest'
gp = GraphProblem(initial, goal, graph)

print(graphSearch(gp))
print(BFS(gp))
print(UCS(gp))
print(DLS(gp))
print(IDLS(gp))
