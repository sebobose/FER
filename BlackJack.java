package zadatak;

/* zadatak sa laboratorijske vjezbe na kolegiju objektno orjentirano programiranje. Ne sjecam se tocno teksta zadatka, ali otprilike je isao ovako: 
 * napisite staticku metodu runBlackJack koja prima string koji predstavlja karte za blackjack odvojene razmakom (npr. 10S KH 5D), gdje zadnje slovo
 * predstavlja simbol karte. Metoda treba vratiti int koji predstavlja zbroj nasih karata ili baca PlayerBustException ako je broj iznad 21.
 * karte J, Q i K predstavljaju broj 10, a A predstavlja 11 ili 1 ako je zbroj presao 21. Zapravo je cilj laboratorijske vjezbe bio da naucimo kako 
 * koristiti iznimke te smo morali i napisati svoju iznimku (PlayerBustException), ali mi se jako dopao zadatak pa sam ga odlucio poslati.
 */
class BlackJack {

	
	public static int runBlackJack(String input) {
		int result = 0;
		if (input.length() == 0) {
			throw new IllegalArgumentException("Input is empty!");
		}
		String[] elements = input.split(" ");
		String[] slova = elements.clone();
		int noofAces = 0;
		for (int i = 0; i < elements.length; ++i) {
			slova[i] = elements[i].substring(elements[i].length() - 1);
			if (!(slova[i].equals("S") || slova[i].equals("C") || slova[i].equals("H") || slova[i].equals("D"))){	//provjera simbola
				throw new IllegalArgumentException("Invalid input String!");
			}
			elements[i] = elements[i].substring(0, elements[i].length()-1);		//micanje simbola
			
			if (elements[i].equals("J") || elements[i].equals("Q") || elements[i].equals("K")) {
				result += 10;
			}
			else if (elements[i].equals("A")) {
				noofAces++;
				result += 11;
			
			}
			else {
				try {
					
				if (Integer.parseInt(elements[i]) <= 10 || Integer.parseInt(elements[i]) >= 2) {
					result += Integer.parseInt(elements[i]);
				}
				else {
					throw new IllegalArgumentException("Invalid input String!");
				}
				}
				catch(NumberFormatException e) {
					throw new IllegalArgumentException("Invalid input String!");
				}
			}
		}
		if (result <= 21) {
			return result;
		}
		else {
			while (noofAces > 0 && result > 21) {
				noofAces--;
				result -= 10;
				
			}
		}
		if (result > 21) {
			throw new PlayerBustException("Player Bust! Try again.");
			
		}
		return result;
	}
}
