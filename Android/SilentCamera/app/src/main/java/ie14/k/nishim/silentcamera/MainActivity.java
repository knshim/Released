package ie14.k.nishim.silentcamera;

import android.hardware.Camera;
import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.util.Calendar;
import java.util.List;

public class MainActivity extends Activity {

    SurfaceView sv;
    SurfaceHolder sh;
    Camera cam;
    Button btn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_main);

        sv = (SurfaceView)findViewById(R.id.surfaceView);
        sh = sv.getHolder();
        sh.addCallback(new SurfaceHolderCallback());

        btn = (Button)findViewById(R.id.btnTakePicture);
        btn.setOnClickListener(new TakePictureClickListener());
    }

    class SurfaceHolderCallback implements SurfaceHolder.Callback {
        @Override
        public void surfaceCreated(SurfaceHolder holder) {
            cam = Camera.open();
            Camera.Parameters param = cam.getParameters();
            List<Camera.Size> ss = param.getSupportedPictureSizes();

            Camera.Size s = ss.get(0);
            for (int i = 0; i < ss.size(); i++) {
                if (ss.get(i).width == 1920) {
                    s = ss.get(i); break;
                }
            }

            param.setPictureSize(s.width, s.height);
            cam.setParameters(param);
        }
        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            try {
                cam.setDisplayOrientation(0);
                cam.setPreviewDisplay(sv.getHolder());

                Camera.Parameters param = cam.getParameters();
                List<Camera.Size> previewSizes =
                        cam.getParameters().getSupportedPreviewSizes();
                Camera.Size size = previewSizes.get(0);
                param.setPreviewSize(size.width, size.height);

                cam.setParameters(param);
                cam.startPreview();
            } catch (Exception e) { }
        }
        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {
            cam.stopPreview();
            cam.release();
        }
    }

    class TakePictureClickListener implements View.OnClickListener {
        @Override
        public void onClick(View v) {
            cam.autoFocus(null);
            cam.takePicture(null, null, new TakePictureCallback());
        }
    }

    class TakePictureCallback implements Camera.PictureCallback {
        @Override
        public void onPictureTaken(byte[] data, Camera camera) {
            try {
                Calendar cal = Calendar.getInstance();
                String fn = String.format("%4d", cal.get(Calendar.YEAR))
                        + String.format("%02d", cal.get(Calendar.MONTH)+1)
                        + String.format("%02d", cal.get(Calendar.DATE))
                        + String.format("%02d", cal.get(Calendar.HOUR_OF_DAY))
                        + String.format("%02d", cal.get(Calendar.MINUTE))
                        + String.format("%02d", cal.get(Calendar.SECOND))+".jpg";

                File dir = new File(
                        Environment.getExternalStorageDirectory(), "SimpleCamera");
                if(!dir.exists()) {
                    dir.mkdir();
                }
                File f = new File(dir, fn);
                FileOutputStream fos = new FileOutputStream(f);
                fos.write(data);
                Toast.makeText(getApplicationContext(),
                        "写真を保存しました", Toast.LENGTH_LONG).show();
                fos.close();
                cam.startPreview();
            } catch (Exception e) { }
        }
    }
}