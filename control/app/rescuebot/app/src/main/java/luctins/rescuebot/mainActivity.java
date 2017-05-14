package luctins.rescuebot;


//Import das classes utilizadas
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.Manifest;

import java.io.IOException;
import java.lang.reflect.Method;
import java.util.Set;
import java.util.UUID;

public class mainActivity extends FragmentActivity implements AdapterView.OnItemClickListener {

    //variáveis Globais
    private TextView btState; //texto de estado do bluetooth
    private static final int REQUEST_ENABLE_BT = 1; //flag do BT
    private BluetoothAdapter myBluetoothAdapter; //Adaptador BT
    private Set<BluetoothDevice> pairedDevices; //Lista de dispositivos Pareados
    private ListView myListView; //lista(visual) de dispositivos encontrados
    private ArrayAdapter<String> BTArrayAdapter; //lista de disp encontrados
    private BluetoothSocket btSocket = null; //socket da conexão
    private Button On, Off, FindBt, ShowBt; //botões
    private Share btdata; //classe para enviar socket bluetooth entre as Activities
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    final int sdk = android.os.Build.VERSION.SDK_INT;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main_activity);

        //"conecta" as ListView's
        myListView = (ListView) findViewById(R.id.deviceList);

        //Configura botões
        On = (Button) findViewById(R.id.buttonOn);
        On.setOnTouchListener(this.listener);
        Off = (Button) findViewById(R.id.buttonOff);
        Off.setOnTouchListener(this.listener);
        FindBt = (Button) findViewById(R.id.buttonSearchDevices);
        FindBt.setOnTouchListener(this.listener);
        ShowBt = (Button) findViewById(R.id.buttonListDevices);
        ShowBt.setOnTouchListener(this.listener);

        //cria instância da classe para armazenar socket bluetooth
        btdata = Share.getInstance();

        //adaptador
        myBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        //lista de dispositivos encontrados pelo adaptador bluetooth
        BTArrayAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);

        //Configura texto que informa estado do Bluetooth
        btState = (TextView) findViewById(R.id.btState);
        btState.setText((myBluetoothAdapter.isEnabled())?("Status: Enabled"):("Status: Disabled"));

        //Configura lista de disposivos bluetooth encontrados
        myListView.setAdapter(BTArrayAdapter);
        myListView.setOnItemClickListener(this);
    }

    //Habilita transceiver bluetooth
    public void on(View view) {
        if (!myBluetoothAdapter.isEnabled()) {
            Intent turnOnIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnOnIntent, REQUEST_ENABLE_BT);

            Toast.makeText(getApplicationContext(),"Bluetooth turned on" ,
                    Toast.LENGTH_SHORT).show();
            btState.setText("Status: Enabled");
        }
        else {
            Toast.makeText(getApplicationContext(),"Bluetooth is already on",
                    Toast.LENGTH_SHORT).show();
        }
    }

    //Desabilita transceiver bluetooth
    public void off(View view) {
        myBluetoothAdapter.disable();
        btState.setText("Status: Disabled");
        Toast.makeText(getApplicationContext(),"Bluetooth turned off",
                Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // TODO Auto-generated method stub
        if(requestCode == REQUEST_ENABLE_BT){
            if(myBluetoothAdapter.isEnabled()) {
                btState.setText("Status: Enabled");
            } else {
                btState.setText("Status: Disabled");
            }
        }
    }

    //Função que configura recepção de dados, e adiciona o dispositivo na lista de dispositivos
    final BroadcastReceiver bReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // pega informações do dipositivo BT encontrado
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                // adiciona nome e endereço MAC a lista
                BTArrayAdapter.add(device.getName() + "\n" + device.getAddress());
                BTArrayAdapter.notifyDataSetChanged();
            }
        }
    };


    //Função para ouvir itens da listView, responsável por iniciar a conexão com disposivito selecionado
    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        // TODO Auto-generated method stub

        //exibe lista de dispositivos na tela
        final String info = ((TextView) view).getText().toString();
        String address = info.substring(info.length()-17);


        Toast.makeText(getApplicationContext(),
                address, Toast.LENGTH_SHORT)
                .show();


        BluetoothDevice device = myBluetoothAdapter.getRemoteDevice(address);

        try {
            btSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            errorExit("Fatal Error", "In onResume() and socket create failed: " + e.getMessage() + ".");
        }

        myBluetoothAdapter.cancelDiscovery();

        try {
            btSocket.connect();
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
                errorExit("Fatal Error", "In onResume() and unable to close socket during connection failure" + e2.getMessage() + ".");
            }
        }

        //passa socket para classe Share
        btdata.store_socket(btSocket);

        Intent control = new Intent(this, controlActivity.class);
        startActivity(control);

    }

    //Lista dispositivos já pareados, armazenando-os no pairedDevices
    public void list(View view){

        pairedDevices = myBluetoothAdapter.getBondedDevices();

        for(BluetoothDevice device : pairedDevices)
            BTArrayAdapter.add(device.getName()+ "\n" + device.getAddress());

        Toast.makeText(getApplicationContext(),"Show'n Paired Devices",
                Toast.LENGTH_SHORT).show();

    }


    //Incia busca por dispositivo bluetooth, mostrando-os na listView
    /*
        Para SDK 23 ou superior (Marshmallow >=) é necessária uma permissão para acesso a localização.
        A variável sdk armazena a versão, configurada quando o aplicativo abre. Apenas pedirá as permissões se
        sdk 23+ for detectada.
    */

    public void find(View view) {

        if(sdk >= 23) {
            Toast.makeText(getApplicationContext(),"SDK 23 Detected",
                    Toast.LENGTH_SHORT).show();

            int permissionCheck = this.checkSelfPermission("Manifest.permission.ACCESS_FINE_LOCATION");
            permissionCheck += this.checkSelfPermission("Manifest.permission.ACCESS_COARSE_LOCATION");
            if (permissionCheck != 0) {

                this.requestPermissions(new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 1001); //Any number
            }
        }

        if (myBluetoothAdapter.isDiscovering()) {
            Toast.makeText(getApplicationContext(),"Find canceled.",
                    Toast.LENGTH_SHORT).show();
            myBluetoothAdapter.cancelDiscovery();
        }
        else {
            Toast.makeText(getApplicationContext(),"Finding",
                    Toast.LENGTH_SHORT).show();
            BTArrayAdapter.clear();
            myBluetoothAdapter.startDiscovery();
            registerReceiver(bReceiver, new IntentFilter(BluetoothDevice.ACTION_FOUND));
        }
    }


    //Listener para a tela, para ouvir os botões da xml e chamar funções de acordo com suas finalidades
    View.OnTouchListener listener = new View.OnTouchListener() {
        @Override
        public boolean onTouch(View view, MotionEvent event) {
            if(event.getAction() == MotionEvent.ACTION_DOWN)
                switch(view.getId()) {
                    case R.id.buttonOn:
                        on(view);
                        break;
                    case R.id.buttonOff:
                        off(view);
                        break;
                    case R.id.buttonSearchDevices:
                        find(view);
                        break;
                    case R.id.buttonListDevices:
                        list(view);
                        break;
                }
            return true;
        }
    };


    //Função para criar socket bluetooth, para estabelecimento da conexão
    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        if(Build.VERSION.SDK_INT >= 10){
            try {
                final Method m = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
                return (BluetoothSocket) m.invoke(device, MY_UUID);
            } catch (Exception e) {
                Log.e("Tela1", "Could not create Insecure RFComm Connection",e);
            }
        }
        return  device.createRfcommSocketToServiceRecord(MY_UUID);
    }

    private void errorExit(String title, String message){
        Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_SHORT).show();
        finish();
    }


    //libera hardware BT quando aplicativo for fechado.
    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
        unregisterReceiver(bReceiver);
        this.finish();
    }

}

