# Bezpieczeństwo Komputerowe - Lista 5

Punkty: ?/20

#### Zad1:
- openssl x509 -in pwr-edu-pl.pem -text -noout
- openssl verify -CAfile pwr-edu-pl.pem -untrusted pwr-edu-pl-chain.pem
- openssl ocsp -issuer pwr-edu-pl-chain.pem -cert pwr-edu-pl.pem -text -url http://GEANT.ocsp.sectigo.com

#### Zad2:
- openssl req -newkey rsa:2048 -keyout key.pem -out MYCSR.csr
- openssl rsa -in key.pem -outform PEM -pubout -out public.pem
- openssl req -in L6/MYCSR.csr -text
