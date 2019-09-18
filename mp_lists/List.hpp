/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
template <class T>
List<T>::List() : length_(0) { 
  // @TODO: graded in MP3.1
   head_ = NULL;
   tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if(tail_!=NULL){
  return List<T>::ListIterator(tail_->next);
  } else{
	return NULL;
  }
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
	ListNode* temp;
	ListNode* current=head_;	
	if(head_==NULL || tail_==NULL){
		return;
	}

	while(current!=NULL){
		temp=current->next;
		delete current;
		current=temp;
		}

	head_=NULL;
	tail_=NULL;
	length_=0;
	
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_=newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_==NULL){
    head_= newNode;
		tail_=newNode;
  }
	else {
    tail_->next= newNode;
		tail_=newNode;
  }


  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  




  ListNode * curr = start;
	if(curr==NULL){
		return curr;
	}



  for (int i = 0; curr != NULL && i<splitPoint; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {

			if(curr->prev!=NULL){
      curr->prev->next = NULL;
			}
			tail_=curr->prev;
			curr->prev=NULL;
  }
  //length_=splitPoint;

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
	if(head_==NULL){
		return;
	}

	if(head_->next==NULL){
		return;

	}


	int i=0;

	ListNode* curr= head_;
	while(curr!=tail_&& curr!=NULL){
		if(i%2==0){
			curr=curr->next;
		} else{
				ListNode* prev= curr->prev;
				ListNode* next= curr->next;
				
				prev->next=next;
				if(next!=NULL){
				next->prev=prev;
				}

				tail_->next=curr;
				curr->prev=tail_;
				curr->next=NULL;

				tail_=curr;
				curr=next;
		}
		i++;
	}
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.Listi
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
	if(startPoint==NULL || endPoint==NULL){
		return;
	}
	
	ListNode* temp;
	ListNode* curr=startPoint;
	ListNode* ListEnd= endPoint->next;
	while(curr!=ListEnd){
		ListNode* temp=curr->prev;
		curr->prev=curr->next;
		curr->next=temp;
		curr=curr->prev;
	}
	
  temp=startPoint;
  startPoint=endPoint;
	endPoint=temp;

}

template <typename T>
void List<T>::reverseNth(ListNode* &head,int n){
	if(head==NULL){
		return;
	}

	ListNode* curr=head;

	for(int i=0;curr->next!=NULL && i<n-1;i++){
		curr=curr->next;
	}

	ListNode* temp=curr->next;

	reverse(head,curr);

	curr->next=temp;

	if(temp==NULL){
		tail_=curr;
		return;
	} else{

	reverseNth(curr->next,n);

  	}

}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
	reverseNth(head_,n);
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

	if(first==NULL && second==NULL){
		return NULL;
	}

  	ListNode dummy;
	dummy.prev=NULL;
	dummy.next=NULL;

	ListNode* curr=&dummy;

	while(1){
	
	if(first==NULL){
		curr->next=second;
		if(curr==&dummy){
		second->prev=NULL;
		} else{
			second->prev=curr;
		}
		break; 																				

	} else if(second==NULL){
		curr->next=first;
		if(curr==&dummy){
		first->prev=NULL;
		} else{


			first->prev=curr;


















		}
		break;

	} else if(first->data<second->data){
		ListNode* temp=first->next;
		first->next=NULL;
		curr->next= first;
		if(curr!= &dummy){
		first->prev=curr;
		} else{
			first->prev=NULL;
		}
		first=temp;
	} else{
		ListNode* temp=second->next;
		second->next=NULL;	
		curr->next=second;
		if(curr!= & 																					
dummy){
		second->prev=curr;
} else{
	second->prev=NULL;
}
		second=temp;
	}


	curr=curr->next;
	}
	return dummy.next;
 
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  if(start==NULL){
	return NULL;
  }

  if(start->next==NULL){
	return start;
  }

  ListNode* curr=start;

  for(int i=0;i<chainLength/2-1;i++){
	curr=curr->next;
  }

  ListNode*  temp=curr->next;
  curr->next=NULL;

  ListNode* first=mergesort(start,chainLength/2);
  ListNode* second=mergesort(temp,chainLength-chainLength/2);

  return merge(first,second);
}
