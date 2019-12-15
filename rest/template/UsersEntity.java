/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.restexample.webapp.users;

import java.io.Serializable;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

/*
 * javax.persistence annotatation: https://docs.oracle.com/javaee/7/api/javax/persistence/package-summary.html
 * javax.validation annotation: https://docs.oracle.com/javaee/7/api/javax/validation/constraints/package-summary.html
 * 
 */

@Entity
@Table(name = "users")
public class UsersEntity implements Serializable {
    
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;
    private String surname;

    public UsersEntity() {
        // Construct default
    }
    
    public UsersEntity(String name, String surname) {
        this.name = name;
        this.surname = surname;
    }
    
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }
}
