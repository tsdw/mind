/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.restexample.webapp.users;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;
import java.util.Optional;
import javax.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping("/api")
public class UsersController {
    
    // Service - dependecy injection
    @Autowired
    private UsersService service;
    
    // Ritorna tutti gli utenti
    @GetMapping("/users")
    public ResponseEntity<List<UsersEntity>> getAllUsers() {
        List<UsersEntity> elements = service.getUsers();
        return ResponseEntity.ok().body(elements);
    }
    
    // Ritorna uno specifico utente
    @GetMapping("/users/{id}")
    public ResponseEntity<UsersEntity> getUser(@PathVariable Long id) {
        Optional<UsersEntity> result = service.getUser(id);
        
        if (!result.isPresent())
            return ResponseEntity.notFound().build();
        
        return ResponseEntity.ok().body(result.get());
    }
    
    // Crea un utente
    @PostMapping("/users")
    public ResponseEntity<UsersEntity> createUser(@Valid @RequestBody UsersEntity user) throws URISyntaxException {
        if (user.getId() != null)
            return ResponseEntity.badRequest().build();
        
        UsersEntity result = service.addUser(user);
        return ResponseEntity.created(new URI("/api/users/" + result.getId())).body(result);
    }
    
    // Aggiorna un utente
    @PutMapping("/users")
    public ResponseEntity<UsersEntity> updateUser(@Valid @RequestBody UsersEntity user) {
        if (user.getId() == null) {
            return ResponseEntity.badRequest().build();
        }
        
        UsersEntity result = service.addUser(user);
        return ResponseEntity.ok().body(user);
    }
    
    // Cancella un utente
    @DeleteMapping("/users/{id}")
    public ResponseEntity<Void> deleteUser(@PathVariable Long id) {
        Optional<UsersEntity> result = service.getUser(id);
        
        if (!result.isPresent()) 
            return ResponseEntity.notFound().build();
        
        service.deleteUser(result.get());
        return ResponseEntity.ok().build();
    }
}
