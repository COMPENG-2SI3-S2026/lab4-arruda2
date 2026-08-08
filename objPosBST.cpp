#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)
    root = nullptr;
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL
    deleteTree();
    root = nullptr;
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree

    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.

    // Traversal order to be used: Post-Order
    // - Ensures that we have a path to all child nodes before deleting root nodes and making them inaccessible

    if(thisNode != nullptr) {
        deleteTree(thisNode->left);
        deleteTree(thisNode->right);
        delete thisNode;
        thisNode = nullptr;
    }

}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.
    return (root == nullptr);
}


bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node

    // Remember, leaf nodes do not have children nodes

    if(thisNode == nullptr) {
        return false;
    } else if(thisNode->data.getPF() == thisPos.getPF()) {
        // Node found, now check if it is a leaf or not
        return (thisNode->left == nullptr && thisNode->right == nullptr);
    } else if(thisPos.getPF() < thisNode->data.getPF()) {
        return isLeaf(thisPos, thisNode->left);    
    } else if(thisPos.getPF() > thisNode->data.getPF()) {
        return isLeaf(thisPos, thisNode->right);
    } else {
        // Do nothing; if item not in tree, recursive call will lead to thisNode == nullptr, and thus return false
        // Assume if all fails, not in tree, so return false regardless
        return false;
    }


}

bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root);
}


void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**

    // print in the format of Prefix + Number
    // e.g.  N30 P25 etc.

    // DO NOT use printObjPos() as it will mess up the game display.
    
    if(thisNode != nullptr) {
        printTree(thisNode->left);
        cout << thisNode->data.getPF() << thisNode->data.getNum() << " ";
        printTree(thisNode->right);
    }

}

void objPosBST::printTree() const  // public interface
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);
}


int objPosBST::getHeight(const TNode* thisNode) const
{
    // Tree Height Calculation Algorithm 

    // 1. If thisNode is null, height is zero.

    // 2. Otherwise, recursively invoke getHeight for the left and right subtree, and save
    //    the returned heights.

    // 3. Compare the two returned heights, and return the larger one.

    if(thisNode == nullptr || (thisNode->left == nullptr && thisNode->right == nullptr)) {
        return 0;

        // Returns 0 if thisNode is null, or if the node is a leaf node (thus accounts for height = n - 1, just inverse to the definition of removing the root)

    } else {

        int leftHeight = getHeight(thisNode->left);
        int rightHeight = getHeight(thisNode->right);

        return (leftHeight > rightHeight)? leftHeight + 1 : rightHeight + 1;
        // Recursively says that if leftHeight is larger, return leftHeight+1, and rightHeight+1 otherwise
        // --> rightHeight+1 returned when rightHeight > leftHeight, or heights are equal (works since either value is the same)

        // Since the base case is defined first, when the leaf nodes are evaluated, leftHeight = rightHeight = 0
        // Therefore, it returns a height of 1 by lH+1 or rH+1 for the parent nodes
        // Recursively doing this allows for the tree's height to be found from the bottom up
        // Performing the comparison ensures only the maximum height is taken as we go up the tree to the root

    }
}

void objPosBST::printCurrentLevel(const TNode* thisNode, const int level) const
{
    // Recursive Level-Order Tree-Printing Algorithm 
    
    // 1. First check if at leaf node.  If yes, do not print anything

    // 2. Then, check if level is 1.  If yes, print the Prefix field only (specified in manual)

    // 3. Otherwise, invoke recursively printCurrentLevel for left subtree with one less level, then
    //                                                        right subtree with one less level
    //    "if I'm not at the level, keep on searching into the left and the right subtrees"

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)

    // Goal is to go through the tree down from the given node, decreasing the level as we go until that level = 1
    // The level decrement and tree traversal should be synced up such that the desired level is hit

    // Out-of-bounds handling
    if(thisNode == nullptr) {
        return;
    }

    // Base case handling
    // level+1 sent as argument to handle expectation that the root is at level 0
    else if(level+1 == 1) {
        cout << thisNode->data.getPF();
    } 
    else if(isLeaf(thisNode->data)) {
        return; // Is this condition necessary, or does the post-order design handle it by default?
    }
    
    else {
        printCurrentLevel(thisNode->left, level-1);
        printCurrentLevel(thisNode->right, level-1);
    }

}

// Public Interface.
void objPosBST::printTreeLevel() const
{
    // Interface to the Recursive Version of Level-Order Tree-Printing Algorithm 

    // 1. Get the height of the tree
    // 2. For each level (bounded by height), invoke the recursive tree-printing algorithm.

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)

    // Design:
    // - Each character will be assigned a "block", with each block having 3 spaces to allow for even spacing when considering negative values
    // - Minimum character space between these blocks will be 3
    // - Root will be in the middle of the space between the blocks
    // - Space between blocks will increase based on the number of nodes total
    // --> Will ensure there is enough space to display all nodes correctly
    // --> Will ensure that if there are not a lot of nodes, the spacing isn't unnecessarily large

    // For this function specifically:
    // - Check height and add spaces accordingly to align levels to be centred over each other
    // - Run printCurrentLevel

    for(int i = 0; i <= getHeight(root); i++) {
        printCurrentLevel(root, i);
        cout << endl;
    }

}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, return true

    if(thisNode == nullptr) {
        return false;
    } else if(thisNode->data.getPF() == thisPos.getPF()) {
        return true;
    } else if(thisPos.getPF() < thisNode->data.getPF()) {
        return isInTree(thisPos, thisNode->left);    
    } else if(thisPos.getPF() > thisNode->data.getPF()) {
        return isInTree(thisPos, thisNode->right);
    } else {
        // Do nothing; if item not in tree, recursive call will lead to thisNode == nullptr, and thus return false
        // Assume if all fails, not in tree, so return false regardless
        return false;
    }

}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)

    // DEBUG STATEMENT
    //if(thisNode != nullptr) {
    //    cout << "Insert " << thisPos.getPF() << " into the BST, compared to " << thisNode->data.getPF() << endl;
    //}

    if(thisNode == nullptr) {
        // We are now at a blank space, and can insert the new node
        //cout << "Insert node into new space" << endl;
        thisNode = new TNode(thisPos);
    } else if(thisPos.getPF() < thisNode->data.getPF()) {
        //cout << thisPos.getPF() << " is < " << thisNode->data.getPF() << endl;
        insert(thisPos, thisNode->left);    
    } else if(thisPos.getPF() > thisNode->data.getPF()) {
        //cout << thisPos.getPF() << " is > " << thisNode->data.getPF() << endl;
        insert(thisPos, thisNode->right);
    } else {
        // Node is already in the tree (prefix match) given all other cases failed
        //cout << "Node already in tree" << endl;
        thisNode->data.setNum(thisPos.getNum() + thisNode->data.getNum());
    }

}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}


const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode

    // Used as part of remove() algorithm

    // Check Lecture Notes for implementation

    if(thisNode == nullptr) {
        return nullptr;
    } else {
        while(thisNode->left != nullptr) {
            thisNode = thisNode->left;
        }
        return thisNode;
    }

}


void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)

    if(thisNode == nullptr) {
        return;

        // Note: This initially also ran for the condition "|| !isInTree(thisPos)"
        // However, this would have led to unnecessary recursive calls throughout the program runtime
        // There are enough if statements in this function to cover all cases, so if the item is not in the tree, it will simply move thisNode to nullptr beyond a leaf and return
    }

    else if(thisPos.getPF() < thisNode->data.getPF()) {
        remove(thisPos, thisNode->left);
    } else if(thisPos.getPF() > thisNode->data.getPF()) {
        remove(thisPos, thisNode->right);
    }
    
    // If above two statements fail, thisPos prefix must == thisNode, and so we can now begin the removal methods
    
    else if(thisNode->left != nullptr && thisNode->right != nullptr) {
        // Case 3 - Delete Node with 2 children
        // Apply Method 1, using findMin
        thisNode->data = findMin(thisNode->right)->data;
        remove(thisNode->data, thisNode->right);
    } else {
        // Cases 1 and 2
        // We are at a node that is either a leaf or has 1 child
        TNode* oldNode = thisNode;
        thisNode = (thisNode->left != nullptr)? thisNode->left : thisNode->right;      // Check left and right; set thisNode to whichever isn't null!
        delete oldNode;
    }

}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.
    
    if(thisNode == nullptr) {
        return false;
    }

    // Perform post-order traversal!
    bool leftTree = findGreater(numThreshold, thisNode->left);
    bool rightTree = findGreater(numThreshold, thisNode->right);
    
    // If neither left nor right subtrees return true, check current node
    // Otherwise, we have found an element greater than numThreshold, and need to return true continuously back to the original recursive call
    return (!leftTree && !rightTree)? thisNode->data.getNum() > numThreshold : true;

}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
