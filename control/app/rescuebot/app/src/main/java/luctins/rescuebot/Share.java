package luctins.rescuebot;

/**
 * Created by luctins on 13/05/17.
 */

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothSocket;

public class Share {
    private BluetoothAdapter myBluetoothAdapter;
    private BluetoothSocket btSocket = null;
    private static Share obj= null;


    public Share(){

    }
    public static Share getInstance(){
        if(obj==null){
            obj = new Share();
        }
        return obj;
    }

    public static void renew_instance(){
        obj = null;
    }

    public void store_socket(BluetoothSocket bt){
        this.btSocket = bt;
    }

    public BluetoothSocket get_socket( ){
        return this.btSocket;
    }

}
