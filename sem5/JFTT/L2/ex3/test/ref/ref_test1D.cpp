#include<iostream>

/** Maly przyklad programu
 * 
 *  // autor Maciej Gebala
 * 
 */



using namespace std;


//! Komentarz dokumentacyjny \
	   i jego // ciag dalszy\
  /* i dalszy */
int some_function(int a) {
	return a << (1 << 4);
}

/*! Nieco inny komentarz dokumentacyjny 

	// Komentarz w komentarzu		
					
					
   */
int main()
{
  /// Komentarz dokumentacyjny \
  ciag dalszy jednolinijkowego komentarza
  int i = 5;
  
  cout << "Jakis program" << endl; 
  
  cout << "Poczatek komentarza /*" << endl; 
  
  //! i jeszcze inny komentarz */
  cout << "Koniec komentarza */ "<< endl; 
  cout << "Komentarz\j /* ala */" << endl;
  /*! I jeszcze jeden
					**/
  
  cout << "Komentarz // kot " << endl;
  cout << "Zabawa \" // ala i kot " << endl;
  cout << "Pulapka \" \\\
           // ma \
           /* ma */ \
           " << endl;
 cout << "Zabawa \" // ala i kot " << endl;	   
 printf("Zabawa \" // ala i kot ");
}
