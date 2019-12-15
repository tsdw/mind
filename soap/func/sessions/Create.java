/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sessions;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 *
 * @author antonino
 */
@WebServlet(name = "Create", urlPatterns = {"/session/create"})
public class Create extends HttpServlet {

    private final String title = "Create session";

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        
        HttpSession session = request.getSession(false);
        
        // Response type
        response.setContentType("text/html;charset=UTF-8");
        
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            
            out.println("<head>");
            out.println("<title>" + title + "</title>");            
            out.println("</head>");
            
            out.println("<body>");
            
            // Effettua il logout se viene ricevuto il parametro logout e session esiste
            if (session != null && request.getParameter("logout") != null) {
                
                // Invalida la sessione
                session.invalidate();
                
                // Redirect to same page
                response.sendRedirect(request.getHeader("referer"));
            }
                            
            // Se la session non esiste
            else if (session == null){
                
                // Title
                out.println("<h3>Esegui l'accesso</h3>");

                // Form input
                out.println("<form action='' method='post'>");

                // Cookie name
                out.println("Username<br>");
                out.println("<input type='text' name=\"username\"><br><br>");

                // Cookie value
                out.println("Password<br>");
                out.println("<input type='text' name=\"password\"><br><br>");

                // Submit
                out.println("<input type='submit' value=\"Login\"><br>");
                out.println("</form>");
            }
            
            // Se la sessione esiste
            else {
                
                // Controlla se la sessione e' stata creata con la presente richiesta
                if (session.isNew()) {
                    out.println("<h3>Accesso eseguito - Informazioni sessione:</h3>");
                }
                else {
                    out.println("<h3>Informazioni sessione:</h3>");
                }
                
                // Session ID
                out.println("Session ID: " + session.getId() + "<br><br>");
                
                // Carico gli attributi della sessione
                Enumeration sessionVar = session.getAttributeNames();
                
                // Print attributi della sessione
                while (sessionVar.hasMoreElements()){
                    String name = sessionVar.nextElement().toString();
                    String value = session.getAttribute(name).toString();
                    
                    out.println("key: " + name + "<br>value: " + value + "<br><br>");
                }
                
                out.println("<a href='?logout'>Effettua il logout</a>");
            }
            
            out.println("</body>");
            out.println("</html>");
        }
    }


    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }


    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Method values from html
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // Se le variabili sono valide creo la sessione
        if (username != null && password != null && username.length() > 0 && password.length() > 0){
            
            // Creo la sessione se non esiste
            HttpSession session = request.getSession(true);
            
            // Setto gli attributi della sessione
            session.setAttribute("username", username);
            session.setAttribute("password", password);
        }   

       // Default process
        processRequest(request, response);
    }
    
}
