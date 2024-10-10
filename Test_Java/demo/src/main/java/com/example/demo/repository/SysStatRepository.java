package com.example.demo.repository;

import com.example.demo.model.SysStat;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface SysStatRepository extends JpaRepository<SysStat, Long> {
}