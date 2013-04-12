import java.util.*;

/**
 * @author sren
 * @version 13-4-12 21:58 Qilinsoft
 */
public class Pbm1181 {

	static LinkedList<String> wordQueue = new LinkedList<String>();

	static Set<String> wordpool = new HashSet<String>();


	public static void main(String[] args) {
		char start = 'b';
		char end = 'm';
		String[] words = new String[]{
				"so",
				"soon",
				"river",
				"goes",
				"them",
				"got",
				"moon",
				"begin",
				"big",
		};
		for (String word : words) {
			wordpool.add(word);
		}
		
		boolean result = find(start, end);
		System.out.println(result);
	}



	public static boolean find(char s, char e){
		addAllWordToQueue(s);
		while (wordQueue.size() > 0) {
			String firstWord = wordQueue.pollFirst();
			System.out.println("check head word: "+firstWord);
			if (checkIfEndWith(firstWord, e)) {
				return true;
			} else {
				char fend = firstWord.charAt(firstWord.length() - 1);
				addAllWordToQueue(fend);
			}
		}
		return false;
	}

	public static boolean checkIfEndWith(String word, char c){
		return word.charAt(word.length()-1)==c;
	}


	public static void addAllWordToQueue(char e){
		Set<String> leftSet = new HashSet<String>();
		int poolSize = wordpool.size();
		for (String word : wordpool) {
			if (e ==word.charAt(0)){
				wordQueue.add(word);
				System.out.println("add "+word+" to queue");
			}else{
				leftSet.add(word);
			}
		}
		if (leftSet.size()==poolSize){
			System.out.println("no word add to queue");
		}else{
		}
		wordpool = leftSet;
		System.out.println(wordQueue.toString());

	}

}
