package ie14.k.nishim.hogequest;

import android.app.Activity;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.os.Bundle;
import android.view.View;
import android.content.Intent;
import android.widget.FrameLayout;

import java.io.IOException;

public class NameActivity extends Activity {

    private MediaPlayer mp;
    private SoundPool sp;
    private int sound_id;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setVolumeControlStream(AudioManager.STREAM_MUSIC);
        setContentView(R.layout.activity_name);

        DragView dv = new DragView(this);
        FrameLayout fl = new FrameLayout(this);
        fl = (FrameLayout)findViewById(R.id.dragView);
        fl.addView(dv);

        //再生ファイルの設定
        mp = MediaPlayer.create(this, R.raw.name_bgm);

        //再生ボリュームの設定(0~1)
        mp.setVolume((float)0.1, (float)0.1);

        //ループ設定
        mp.setLooping(true);

        //再生開始
        mp.start();

        //(ロードするファイルの数, ストリームのタイプ, サンプリングレートのクオリティ)
        sp = new SoundPool( 1, AudioManager.STREAM_MUSIC, 0 );

        //ロード
        sound_id = sp.load(this, R.raw.button_se, 1 );
    }

    public void onClick(View view){

        //停止
        mp.stop();
        try {
            mp.prepare();
        } catch (IOException e){}

        //再生(ロードした時のID, 左側の音量, 右側の音量, プライオリティ優先度, ループ指定-1：無限ループ0：一回再生, 再生速度0.5～2.0まで1.0で普通の速度)
        sp.play(sound_id, 0.5F, 0.5F, 0, 0, 1.5F);

        switch (view.getId()){
            case R.id.titleButton:
                Intent intentTitle = new Intent(this, TitleActivity.class);
                startActivity(intentTitle);
                break;
            case R.id.enterButton:
                Intent intentEnter = new Intent(this, TitleActivity.class);
                startActivity(intentEnter);
                break;
        }
    }

}