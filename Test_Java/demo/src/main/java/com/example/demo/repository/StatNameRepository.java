package com.example.demo.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import com.example.demo.model.StatName;

public interface StatNameRepository extends JpaRepository<StatName, Integer> {
}