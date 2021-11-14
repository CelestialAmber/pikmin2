#ifndef _JSYSTEM_JSU_JSUPTRLIST_H
#define _JSYSTEM_JSU_JSUPTRLIST_H

#include "types.h"

struct JSUPtrLink;

// Size: 0xC
struct JSUPtrList {
	JSUPtrLink* getFirstLink() const;
	// JSUPtrList() { initiate(); }
	JSUPtrList(bool = true);
	~JSUPtrList();
	void initiate();
	bool append(JSUPtrLink*);
	bool prepend(JSUPtrLink*);
	bool insert(JSUPtrLink*, JSUPtrLink*);
	bool remove(JSUPtrLink*);
	JSUPtrLink* getNthLink(ulong) const;

	JSUPtrLink* m_head; // _00
	JSUPtrLink* m_tail; // _04
	int m_linkCount;    // _08
};

// Something fishy here. JSULists can use JSUPtrList functions.
// They even use its constructor??? (see _sinit_JKRThread_cpp)
template <typename T> struct JSUList : public JSUPtrList {
	inline T* getHead() {
		return m_head;
	}
	inline T* getTail() {
		return m_tail;
	};
};

#endif
