#include<bits/stdc++.h>
using namespace std;
#define MAX_CHAR 256

// Node structure for suffix tree
struct Node {
	struct Node *children[MAX_CHAR];
	struct Node *link;
	int start;
	int *end;
	int index;
};

typedef struct Node SuffixNode;

char input_text[100];
SuffixNode *root_node = NULL;
SuffixNode *last_new_node = NULL;
SuffixNode *active_node = NULL;
int active_edge = -1;
int active_length = 0;
int remaining_suffix_count = 0;
int leaf_end = -1;
int *root_end = NULL;
int *split_end = NULL;
int text_length = -1;

// Create a new node for suffix tree
SuffixNode *createNewNode(int start, int *end) {
	SuffixNode* new_node = new SuffixNode();
	int i;
	for (i = 0; i < MAX_CHAR; i++)
		new_node->children[i] = NULL;
	new_node->link = root_node;
	new_node->start = start;
	new_node->end = end;
	new_node->index = -1;
	return new_node;
}

// Calculate the length of an edge represented by a node
int edgeLength(SuffixNode *node) {
	if(node == root_node)
		return 0;
	return *(node->end) - (node->start) + 1;
}

// Move down in the tree based on the active point
int moveDown(SuffixNode *current_node) {
	if (active_length >= edgeLength(current_node))
	{
		active_edge += edgeLength(current_node);
		active_length -= edgeLength(current_node);
		active_node = current_node;
		return 1;
	}
	return 0;
}

// Extend the suffix tree based on Ukkonen's algorithm
void extendSuffixTree(int position) {
	leaf_end = position;
	remaining_suffix_count++;
	while(remaining_suffix_count > 0) {
		if (active_length == 0)
			active_edge = position;

		if (active_node->children[input_text[active_edge]] == NULL) {
			active_node->children[input_text[active_edge]] = createNewNode(position, &leaf_end);
			if (last_new_node != NULL) {
				last_new_node->link = active_node;
				last_new_node = NULL;
			}
		}
		else {
			SuffixNode *next_node = active_node->children[input_text[active_edge]];
			if (moveDown(next_node)) {
				continue;
			}
			if (input_text[next_node->start + active_length] == input_text[position]) {
				if(last_new_node != NULL && active_node != root_node) {
					last_new_node->link = active_node;
					last_new_node = NULL;
				}
				active_length++;
				break;
			}
			split_end = new int;
			*split_end = next_node->start + active_length - 1;
			SuffixNode *split_node = createNewNode(next_node->start, split_end);
			active_node->children[input_text[split_node->start]] = split_node;
			split_node->children[input_text[position]] = createNewNode(position, &leaf_end);
			next_node->start += active_length;
			split_node->children[input_text[next_node->start]] = next_node;
			if (last_new_node != NULL) {
				last_new_node->link = split_node;
			}
			last_new_node = split_node;
		}
		remaining_suffix_count--;
		if (active_node == root_node && active_length > 0) {
			active_length--;
			active_edge = position - remaining_suffix_count + 1;
		}
		else if (active_node != root_node) {
			active_node = active_node->link;
		}
	}
}

// Print a substring of the input text
void printSubstring(int start_index, int end_index) {
	int i;
	for (i=start_index; i<=end_index && input_text[i] != '#'; i++){
		cout << input_text[i];
	}
	if(i <= end_index)
		cout << "#";
}

// Set suffix indices for each node in the suffix tree using DFS
void setSuffixIndexByDFS(SuffixNode *node, int label_height) {
	if (node == NULL) return;
	if (node->start != -1) {
		printSubstring(node->start, *(node->end));
	}
	int is_leaf = 1;
	int i;
	for (i = 0; i < MAX_CHAR; i++) {
		if (node->children[i] != NULL) {
			if (is_leaf == 1 && node->start != -1){
				cout << " [" << node->index << "]" << endl;
			}
			is_leaf = 0;
			setSuffixIndexByDFS(node->children[i], label_height + edgeLength(node->children[i]));
		}
	}
	if (is_leaf == 1) {
		for(i= node->start; i<= *(node->end); i++) {
			if(input_text[i] == '#') {
				node->end = new int;
				*(node->end) = i;
			}
		}
		node->index = text_length - label_height;
		cout << " [" << node->index << "]" << endl;
	}
}

// Free memory allocated for suffix tree nodes in a post-order traversal
void freeSuffixTreeByPostOrder(SuffixNode *node) {
	if (node == NULL)
		return;
	int i;
	for (i = 0; i < MAX_CHAR; i++) {
		if (node->children[i] != NULL) {
			freeSuffixTreeByPostOrder(node->children[i]);
		}
	}
	if (node->index == -1)
		delete node->end;
	delete node;
}

// Build the suffix tree for the input text
void buildSuffixTree() {
	text_length = strlen(input_text);
	int i;
	root_end = new int;
	*root_end = - 1;
	root_node = createNewNode(-1, root_end);
	active_node = root_node;
	for (i=0; i<text_length; i++)
		extendSuffixTree(i);
	int label_height = 0;
	setSuffixIndexByDFS(root_node, label_height);
	freeSuffixTreeByPostOrder(root_node);
}

// Driver function
int main() {
	strcpy(input_text, "xabxa#babxba$");
	buildSuffixTree();
	return 0;
}
