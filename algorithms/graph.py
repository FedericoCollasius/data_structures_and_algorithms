from typing import Any, NoDefault, Optional, Dict, List, Tuple, Set

class Node:
    def __init__(self, value: Any) -> None:
        self.value = value
        self.visited: bool = False
        self.distance: Optional[float] = None
        self.parent: Optional['Node'] = None
    
    # object type because it should handle any type we pass it
    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Node):
            return False
        return self.value == other.value

    def __hash__(self) -> int:
        return hash(self.value)

class Graph:
    def __init__(self, directed: bool = False, multi_edge: bool = False,
                 negative_edge: bool = False) -> None:
        # node -> [(neighbour, weight), (neighbour, weight)...]
        self._graph: Dict[Node, List[Tuple[Node, float]]] = {}        
        self._nodes: Set[Node] = set()
        self._directed:bool = directed
        self._multi_edge: bool = multi_edge 
        self._negative_edge: bool = negative_edge
    
    # Nodes
    def get_nodes(self) -> Set[Node]:
        return set(self._nodes)

    def add_node(self, v: Node) -> bool:
        try:
            if v in self._nodes:
                return False
            self._graph[v] = []
            self._nodes.add(v)
            return True
        except Exception as e:
            raise RuntimeError(f"Unexpected error when adding node: {str(e)}")
    
    def remove_node(self, v: Node) -> bool:
        if v not in self._nodes:
            raise ValueError("Node must exist in the graph")
        
        try:
            for u in self._nodes:
                if u != v:
                    self._graph[u] = [
                        (w, weight) for w, weight in self._graph[u]
                        if u != v
                    ]
            del self._graph
            self._nodes.remove(v)
            return True
        except Exception as e:
            raise RuntimeError(f"Unexpected error when removing node: {str(e)}")

    # Edges
    def get_edges(self) -> Dict[Node, List[Tuple[Node, float]]]
        edges = []
        seen = set()

        for v in self_nodes:
            for u, weight in self._graph[v]:
                if self._directed:
                    edges.append((v, u, weight))
                else:

    def add_edge(self, v: Node, u: Node, weight: float=0.0) -> bool:
        if v not in self._nodes or u not in self._nodes:
            raise ValueError("Both nodes must exist in the graph")
        
        if not self._negative_edge and weight < 0.0:
            raise ValueError("Weight cannot be negative")

        try:
            if not self._multi_edge:
                for neighbour, _ in self._graph[v]:
                    if neighbour == u:
                        return False

            self._graph[v].append((u, weight))
            if not self._directed:
                self._graph[u].append((v, weight))
            return True
                
        except Exception as e:
            raise RuntimeError(f"Unexpected error when adding edge: {str(e)}")
    
    def remove_edge(self, v: Node, u: Node) -> bool:
        if v not in self._nodes or u not in self._nodes:
            raise ValueError("Both nodes must exist in the graph")

        try:
            v_edges = self._graph[v]
            for i, (w, _) in enumerate(v_edges):
                if w == u:
                    v_edges.pop(i)
                    if not self._directed:
                        u_edges = self._graph[u]
                        for j, (w, _) in enumerate(u_edges):
                            if w == v:
                                u_edges.pop(j)
                                break
                    return True
            return False
        except Exception as e:
            raise RuntimeError(f"Unexpected error when removing edge: {str(e)}")
