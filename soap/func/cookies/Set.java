/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cookies;

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author antonino
 */
@WebServlet(name = "Set", urlPatterns = {"/cookies/set"})
public class Set extends HttpServlet {

    private final String title = "Set Cookie";
    
    
    // Metodo in comune condiviso da POST e GET
    protected void requestCommon(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
                
        // Setto il cookie
        String name = request.getParameter("name");
        String value = request.getParameter("value");
        Cookie cookie = null;
        
        // Se le variabili non sono vuote setto il cookie
        if (name != null && value != null && name.length() > 0 && value.length() > 0){
            cookie = new Cookie(name, value);
            response.addCookie(cookie);
        }   
        
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
            
            // Title
            out.println("<h2>Compila il form per creare un Cookie</h2>");
           
            // Form input
            out.println("<form action='' method='post'>");

            // Cookie name
            out.println("Name<br>");
            out.println("<input type='text' name=\"name\"><br><br>");

            // Cookie value
            out.println("Value<br>");
            out.println("<input type='text' name=\"value\"><br><br>");

            // Submit
            out.println("<input type='submit' value=\"Conferma\"><br>");
            out.println("</form>");

            
            // Stampa il cookie appena creato
            if (cookie != null) {
                out.println("<h2>Cookie creato:</h2>");
                out.println("name: " + cookie.getName() + " value: " + cookie.getValue() + "<br>");
            }
            
            
            // Stampa la lista dei cookie salvati
            Cookie[] listCookie = request.getCookies();
      
            if (listCookie.length > 0){
                out.println("<h2>Cookies salvati:</h2>");
                
                for (int i=0; i < listCookie.length; i++){
                    out.println("name: " + listCookie[i].getName() + " value: " + listCookie[i].getValue() + "<br>");
                }
            }
            
            out.println("</body>");
            out.println("</html>");
        }
    }
     
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
       
        requestCommon(request, response);
    }


    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        requestCommon(request, response); 
    }
}
