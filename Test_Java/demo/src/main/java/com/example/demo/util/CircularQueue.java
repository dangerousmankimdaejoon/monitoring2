package com.example.demo.util;

import java.util.LinkedList;

public class CircularQueue<T> {
    private final int maxSize;
    private final LinkedList<T> queue;

    public CircularQueue(int maxSize) {
        this.maxSize = maxSize;
        this.queue = new LinkedList<>();
    }

    public void add(T element) {
        if (queue.size() == maxSize) {
            queue.poll();
        }
        queue.add(element);
    }

    public LinkedList<T> getAll() {
        return new LinkedList<>(queue);
    }

    public int size() {
        return queue.size();
    }
}