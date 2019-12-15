/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.restexample.webapp.users;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

// IMPORTANTE: La repository va dichiarata come interfaccia che estende da CrudRepository i metodi di default

@Repository
public interface UsersRepository extends CrudRepository<UsersEntity, Long> {
    
    // Default crud methods: https://docs.spring.io/spring-data/commons/docs/current/api/org/springframework/data/repository/CrudRepository.html
    
    // Metodi aggiunti manualmente
    
}
