# Max Flow Min Cut Simulation

This is an interactive C++/SFML application that provides a visual, step-by-step simulation of the **Ford-Fulkerson algorithm** to find the maximum flow in a directed graph.

The simulation displays both the **Flow Network** (showing current flow and capacity) and the **Residual Graph** at each iteration of the algorithm.


## Features

* **Visual Algorithm**: Watch the Ford-Fulkerson algorithm run step-by-step.
* **Step-by-Step Navigation**: Use the arrow keys to move forward and backward through each augmenting path and residual graph calculation.
* **Interactive Graph**: Click and drag nodes to rearrange the graph layout for better visibility.
* **Clear Data Display**: A dynamic table on the side of the window shows the capacities and flows for each edge, or the forward/backward residual capacities.
* **Augmenting Path Highlighting**: The algorithm highlights the augmenting path found by the DFS in the residual graph at each step.
* **Dynamic Results**: The "Net Flow" and "BottleNeck" values update with each iteration.

## How It Works

The application implements the Ford-Fulkerson algorithm to find the maximum flow from a source node ('s') to a sink node ('t').

1.  **Initialization**: The algorithm starts with zero flow across all edges.
2.  **Build Residual Graph**: A residual graph is constructed based on the current flow.
    * **Forward Edges**: For an edge `(u, v)` with `capacity` and `flow`, a forward residual edge `(u, v)` is created with residual capacity `capacity - flow`.
    * **Backward Edges**: A backward residual edge `(v, u)` is created with residual capacity `flow`.
3.  **Find Augmenting Path**: The algorithm uses a Depth-First Search (DFS) to find *any* path from 's' to 't' in the residual graph that has capacity greater than 0.
4.  **Augment Flow**:
    * If no path is found, the algorithm terminates. The current flow is the maximum flow.
    * If a path is found, the **bottleneck capacity** (the minimum residual capacity along the path) is identified.
    * This bottleneck value is then "pushed" through the network. The flow is increased on all forward edges in the path and decreased on all backward edges.
5.  **Repeat**: The process repeats from Step 2 with the new flow values.

This simulation stores each of these states (both the flow graph and the residual graph) and allows you to browse through them.

## How to Use

### Controls

* **Left Arrow**: Go to the previous step in the simulation.
* **Right Arrow**: Go to the next step in the simulation.
* **Click and Drag Node**: Rearrange the graph by dragging a node.
* **'E' Key**: Exit the simulation.

### Input

The graph is loaded from the `take_input.txt` file. The format is:

1.  **First line**: `N M` (Number of nodes, Number of edges)
2.  **Next `M` lines**: `u v c f` (Start node, End node, Capacity, Initial flow)

*Note: Nodes are 1-indexed in the input file but are converted to 0-indexed internally. The source is assumed to be node `1` and the sink is node `N`.*

**Example `take_input.txt`:**lo