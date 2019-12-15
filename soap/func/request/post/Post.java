/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package request.post;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

        
/**
 *
 * @author antonino
 */
@WebServlet(name = "Post", urlPatterns = {"/request/post"})
public class Post extends HttpServlet {

    String title;
    
    /*
     * Questo metodo fa parte della classe GenericServlet
     * E' il primo metodo richiamato dal container quando una servlet viene eseguita
     */
    
    @Override
    public void init() throws ServletException {
        title = "POST Request - response";
    }
    
    
   // Funzione per processare la richiesta di tipo GET
    protected void processPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Prendo il valore delle variabili inviate dal client
        String username = request.getParameter("username");
        String surname = request.getParameter("password");
           
        // Response type
        response.setContentType("text/html;charset=UTF-8");
        
        // Scrittura nel buffer di risposta
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            
            out.println("<head>");
            out.println("<title>" + title + "</title>");            
            out.println("</head>");
            
            out.println("<body>");
            
            // Controllo se i campi sono stati settati
            if (username.isEmpty() || surname.isEmpty()){
                out.println("E' necessario riempire entrambi i campi<br>");
            }
            
            // Se i campi sono stati settati allora:
            else {
                out.println("<h3>POST Request response</h3>");
                out.println("Parametri ricevuti:<br>");
                out.println("username = " + username + "<br>");
                out.println("password =  " + surname + "<br>");
            }
            
            out.println("</body>");
            
            out.println("</html>");
        }
    }


    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        processPost(request, response);
    }

}
