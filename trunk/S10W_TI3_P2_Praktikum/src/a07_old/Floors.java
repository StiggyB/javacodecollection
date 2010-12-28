package a07_old;

public enum Floors {
    GROUNDFLOOR,
    FIRSTFLOOR,
    SECONDFLOOR,
    THIRDFLOOR;
    
    public int toInteger(){
        int resu = 0;
        
        switch ( this ) {
            case GROUNDFLOOR    : resu = 0; break;
            case FIRSTFLOOR : resu = 1; break;
            case SECONDFLOOR   : resu = 2; break;
            case THIRDFLOOR  : resu = 3; break;
        }//switch
        
        return resu;
    }//toString
   
}
