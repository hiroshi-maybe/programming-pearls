//
//  Heap.swift
//  
//
//  Created by kori on 8/6/16.
//
//

import Foundation

struct Heap {
  var elements: [Int] = []
  
  mutating func extractMin() -> Int? {
    guard let minV = value(0),
      lastV = elements.last else { return nil }
    
    elements.removeLast()
    elements[0] = lastV
    
    shiftdown(0)
    
    return minV
  }
  
  mutating func shiftdown(idx: Int) {
    guard let myvalue = value(idx) else { return }
    let leftV = leftChild(idx) ?? Int.max
    let rightV = rightChild(idx) ?? Int.max
    
    let swappingIdx = leftV < rightV ? leftChildIdx(idx) : rightChildIdx(idx)
    let swappingV = min(leftV, rightV)
    
    guard swappingV < myvalue else { return }
    
    elements[swappingIdx] = myvalue
    elements[idx] = swappingV
    
    shiftdown(swappingIdx)
  }
  
  mutating func insert(n: Int) {
    elements.append(n)
    shiftup_rec(elements.count - 1)
  }
  
  mutating func shiftup_rec(idx: Int) {
    guard let parent = parent(idx),
      myvalue = value(idx) else { return }
    
    if parent > myvalue {
      elements[parentIdx(idx)] = myvalue
      elements[idx] = parent
      shiftup_iter(parentIdx(idx))
    }
  }
  
  mutating func shiftup_iter(idx: Int) {
    // elements[idx] does not fill heap property
    
    var current = idx
    
    while let parent = parent(current),
      myvalue = value(current) where parent > myvalue {
        // has parent, parent > myvalue
        
        elements[parentIdx(current)] = myvalue
        elements[current] = parent
        current = parentIdx(current)
    }
  }
  
  func parentIdx(idx: Int) -> Int {
    return idx / 2
  }
  
  func parent(idx: Int) -> Int? {
    guard idx != 0 else { return nil }
    let pidx = parentIdx(idx)
    return value(pidx)
  }
  
  func value(idx: Int) -> Int? {
    guard idx < elements.count else { return nil }
    return elements[idx]
  }
  
  func leftChildIdx(idx: Int) -> Int {
    return 2 * idx + 1
  }
  
  func leftChild(idx: Int) -> Int? {
    let cidx = leftChildIdx(idx)
    return value(cidx)
  }
  
  func rightChildIdx(idx: Int) -> Int {
    return 2 * idx + 2
  }
  
  func rightChild(idx: Int) -> Int? {
    let cidx = rightChildIdx(idx)
    return value(cidx)
  }
}

var heap = Heap()
heap.insert(3)
heap.insert(5)
heap.insert(1)
heap.insert(2)
heap.insert(4)

assert(heap.elements == [1,2,4,3,5])

let minValue = heap.extractMin()
assert(minValue == 1)
assert(heap.elements == [2,3,4,5])
