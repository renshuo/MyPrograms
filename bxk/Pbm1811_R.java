import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

/**
 * @author sren
 * @version 13-4-12 22:59 Qilinsoft
 */
public class Pbm1811_R {

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
		Set<String> wordSet = new HashSet<String>();
		for (String word : words) {
			wordSet.add(word);
		}

		LinkedList<String> path = new LinkedList<String>();
		boolean result = find(start, end, wordSet, path);
		System.out.println(result);
		System.out.println(path.toString());
	}



	static boolean find(char s, char e, Set<String> words, LinkedList<String> path){
		for (String word : words) {
			if (word.charAt(0)==s){
				System.out.println("check word: "+word);
				if (word.charAt(word.length() - 1) == e){
					System.out.println("get it : "+word);
					path.addLast(word);
					return true;
				}else{
					char end = word.charAt(word.length()-1);
					if (find(end, e, words, path)){
						path.addFirst(word);
						return true;
					}
				}
			}
		}
		return false;
	}


}
