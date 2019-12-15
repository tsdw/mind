/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package request.get;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


// Mapping del percorso servlet tramite codice, senza utilizzare web.xml
@WebServlet(name = "Get", urlPatterns = {"/request/get"})


public class Get extends HttpServlet {

    String title;
    
    /*
     * Questo metodo fa parte della classe GenericServlet
     * E' il primo metodo richiamato dal container quando una servlet viene eseguita
     */
    
    @Override
    public void init() throws ServletException {
        title = "GET Request - response";
    }
    
    
   // Funzione per processare la richiesta di tipo GET
    protected void processGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Prendo il valore delle variabili inviate dal client
        String name = request.getParameter("name");
        String surname = request.getParameter("surname");
           
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
            if (name.isEmpty() || surname.isEmpty()){
                out.println("E' necessario riempire entrambi i campi<br>");
            }
            
            // Se i campi sono stati settati allora:
            else {
                out.println("<h3>GET Request response</h3>");
                out.println("Parametri ricevuti:<br>");
                out.println("name = " + name + "<br>");
                out.println("surname =  " + surname + "<br>");
            }
            
            out.println("</body>");
            
            out.println("</html>");
        }
    }


    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processGet(request, response);
    }
}
