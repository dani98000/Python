package il.co.ilrd.exam.ds1;

import java.util.ArrayList;
import java.util.List;

public class Graph {
	List<Node> nodes = new ArrayList<>();;
	
	static class Node {
		List<Node> connectedNodes = new ArrayList<>();;
		int UID;
		char type;
		
		public Node(int UID, char type) {
			this.UID = UID;
			this.type = type;
			connectedNodes.add(this);
		}

		public List<Node> getConnectedNodes() {
			return connectedNodes;
		}
		
		public void AddToConnectedNodes(Node node) {
			connectedNodes.add(node);
		}

		public int getUID() {
			return UID;
		}

		public char getType() {
			return type;
		}
	}
	
	public void AddToNodesList(Node node) {
		nodes.add(node);
	}
	
	public static Graph CreateGraph() {
		Graph graph = new Graph();
		Node node1 = new Node(1, 'A');
		Node node2 = new Node(2, 'B');
		Node node3 = new Node(3, 'D');
		Node node4 = new Node(4, 'A');
		Node node5 = new Node(5, 'C');
		Node node6 = new Node(6, 'B');
		Node node7 = new Node(7, 'E');
		Node node8 = new Node(8, 'C');

		graph.AddToNodesList(node1);
		graph.AddToNodesList(node2);
		graph.AddToNodesList(node3);
		graph.AddToNodesList(node4);
		graph.AddToNodesList(node5);
		graph.AddToNodesList(node6);
		graph.AddToNodesList(node7);
		graph.AddToNodesList(node8);
		
		node1.AddToConnectedNodes(node2);
		node2.AddToConnectedNodes(node1);
		node2.AddToConnectedNodes(node5);
		node2.AddToConnectedNodes(node3);
		node3.AddToConnectedNodes(node2);
		node4.AddToConnectedNodes(node5);
		node4.AddToConnectedNodes(node6);
		node4.AddToConnectedNodes(node7);
		node5.AddToConnectedNodes(node2);
		node5.AddToConnectedNodes(node4);
		node5.AddToConnectedNodes(node6);
		node6.AddToConnectedNodes(node5);
		node6.AddToConnectedNodes(node4);
		node6.AddToConnectedNodes(node8);
		node7.AddToConnectedNodes(node4);
		node8.AddToConnectedNodes(node6);
		
		return graph;
	}
	
	public void FindAllInstances(char[] pattern) {
		int size = pattern.length;
		int i = 0;
		
		for(Node node : nodes) {
			if(node.getType() == pattern[i]) {
				CheckConnections(i + 1, pattern, node, size, "" + node.UID);
			}
		}		
	}
	
	private static void CheckConnections(int index, char[] pattern, Node node,int size, String curr){
		if(index >= size) {
			System.out.println(curr);;
			return;
		}
		
		for(Node node1 : node.getConnectedNodes())
			if(node1.getType() == pattern[index]) {
				CheckConnections(index + 1, pattern, node1, size, curr + node1.UID);
			}
		}
}
