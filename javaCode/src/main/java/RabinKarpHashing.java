/**
 * Created by nagasaty on 11/4/17.
 */
public class RabinKarpHashing {
    RabinKarpHashing(){
        
    }

    /**
     * @param c Only ATGC (uppercase) are supported. A=0, T=1, G=2, C=3 ..else returns -1
     * @return returns the index
     */
    public int getIndex(char c){
        return (c=='A')?0:((c=='T')?1:((c=='G')?2:(c=='C')?3:-1));
    }
    
    public long hash(String kmer, int sigma){
        long res = 0 ;
        for (char c : kmer.toCharArray()) {
            res = res*sigma + getIndex(c);
        }
        return res;
    }
}
