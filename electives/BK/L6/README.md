# Bezpieczeństwo Komputerowe - Lista 5

Punkty: 20/20

#### Zad 1:
- openssl x509 -in pwr-edu-pl.pem -text -noout
- openssl verify -CAfile pwr-edu-pl.pem -untrusted pwr-edu-pl-chain.pem
- openssl ocsp -issuer pwr-edu-pl-chain.pem -cert pwr-edu-pl.pem -text -url http://GEANT.ocsp.sectigo.com

#### Zad 2:
- openssl req -newkey rsa:2048 -keyout key.pem -out MYCSR.csr
- openssl rsa -in key.pem -outform PEM -pubout -out public.pem
- openssl req -in L6/MYCSR.csr -text

#### Zad 3:
1.
    2. f12 - wpisz alert(document.cookie) w konsoli na paru kartach
    7. credit number - ```"<script>alert();</script>```
    10. ```start.mvc#test``` - f12 -> debugger -> webgoat -> goatapp -> view -> GoatRouter -> linia 52
    11. ```http://localhost:8080/WebGoat/start.mvc#test/<script>webgoat.customjs.phoneHome();<%2fscript>``` -> f12 -> skopiuj phone home said -> response


2.
    3. ```"<script>webgoat.customjs.phoneHome();</script>```


3.
    5.  Chronimy pola przed wykonywaniem skryptów:
        ```<%@taglib prefix"e" uri="https://www.owasp.org/index.php/OWASP_Java_Encoder_Project" %>```
        
        1. ```YOUR CODE HERE -> ${e:forHtml(param.first_name)}```
        2. ```YOUR CODE HERE -> ${e:forHtml(param.last_name)}```
    
    6.  To samo tylko w javie:
    ```
        import org.owasp.validator.html.*;
        import MyCommentDAO;

        public class AntiSamyController {
            public void saveNewComment(int threadID, int userID, String newComment){
                Policy p = Policy.getInstance("antisamy-slashdot.xml");
                AntiSamy as = new AntiSamy();
                CleanResults clean = as.scan(newComment, p);
                MyCommentDAO.addComment(threadID, userID, clean.getCleanHTML());  
            }
        }
    ```
 

