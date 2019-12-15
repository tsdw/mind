/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.restexample.webapp.users;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/*
 * CrudRepository method: https://docs.spring.io/spring-data/commons/docs/current/api/org/springframework/data/repository/CrudRepository.html
 */

@Service
public class UsersService {
    
    // Repository - dependecy injection
    @Autowired
    private UsersRepository repository;
    
    public UsersEntity addUser(UsersEntity user) {
        return repository.save(user);
    }
    
    // Optional: https://docs.oracle.com/javase/8/docs/api/java/util/Optional.html
    public Optional<UsersEntity> getUser(Long id) {
        return repository.findById(id);
    }
    
    // Iterable: https://docs.oracle.com/javase/8/docs/api/java/lang/Iterable.html?is-external=true
    public List<UsersEntity> getUsers() {
        List<UsersEntity> elements = new ArrayList<>();
        repository.findAll().forEach(x -> elements.add(x));
        return elements;
    }
    
    public UsersEntity updateUser(UsersEntity user) {
        return repository.save(user);
    }
    
    public void deleteUser(UsersEntity user) {
        repository.delete(user);
    }
}
