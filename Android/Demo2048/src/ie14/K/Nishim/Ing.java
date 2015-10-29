package ie14.K.Nishim;

import java.util.Random;

import android.app.Activity;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.TextView;



//--------------------------------------------------------------------------
//メイン
//--------------------------------------------------------------------------
public class Ing extends Activity{

    static TextView tv;
    static ImageView[] iv = new ImageView[16];
    static int[] resId = new int [16];

    static int field[][] = new int[4][4];
    static int score;

    static Random rnd = new Random();
    static int i, j, s, t, x, y, cnt;

	static SoundPool sp;
	static int sound_id;

	public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ing);

        DragView dv = new DragView(this);
        FrameLayout fl = new FrameLayout(this);
        fl = (FrameLayout)findViewById(R.id.FrameLayout2);
        fl.addView(dv);

        sp = new SoundPool( 1, AudioManager.STREAM_MUSIC, 0 );
        sound_id = sp.load(this, R.raw.effect, 1 );


        //スコアを初期化
        score = 0;

    	//ボードを0で初期化
        for(i = 0; i < 4; i++){
        	for(j = 0; j < 4; j++){
        		field[i][j] = 0;
        	}
        }

        //リソースIDからテキストビューを設定
        tv = (TextView) this.findViewById(R.id.textView2);

    	//リソースIDからイメージビューを設定
    	for(i = 0; i < 16; i++){
    		resId[i] = getResources().getIdentifier("imageView" + (i + 1), "id", this.getPackageName());
    		iv[i] = (ImageView) this.findViewById(resId[i]);
		}

    	//画像ファイルのリソースIDを設定
    	resId[0] = getResources().getIdentifier("peace0", "drawable", this.getPackageName());
    	for(i = 1,j = 2; j <= 2048 ; i++,j *= 2){
    		resId[i] = getResources().getIdentifier("peace" + j, "drawable", this.getPackageName());
    	}

    	//ボードにランダムで2を2つ配置
    	cnt = 0;
    	while(cnt < 2){
    		x = (int)(rnd.nextInt(100) % 4);
    		y = (int)(rnd.nextInt(100) % 4);
    		if(field[x][y] == 0){
    			field[x][y] = 2;
    			cnt++;
    		}
    	}
    	refleshImage();

    	// タイトル画面へ戻るボタンを設定
    	Button bt = (Button)findViewById(R.id.buttonBack);
    	bt.setOnClickListener(new View.OnClickListener() {
    		public void onClick(View v) {
    			finish();
    		}
    	});
	}

	//--------------------------------------------------------------------------
	//フリックされた方向に応じて処理をする
	//--------------------------------------------------------------------------
	public static void FlickEvent(int direction){

		//移動元座標
		int startMoveY = 0;
		int startMoveX = 0;

		//移動先座標
		int endMoveY = 0;
		int endMoveX = 0;

		//移動先座標(1マス先)
		int toMoveY = 0;
		int toMoveX = 0;

		//変化量
		int changeY = 0;
		int changeX = 0;

		//移動元座標,移動先座標,変化量,ポップ座標を決定(移動方向に応じて移動順序が異なるため)
		switch(direction){
			case 0:
				startMoveY = 1;
				startMoveX = 0;
				endMoveY = 4;
				endMoveX = 4;
				toMoveY = -1;
				toMoveX = 0;
				changeY = 1;
				changeX = 1;
				x = 3;
				y = (int)(rnd.nextInt(100) % 4);
				break;
			case 1:
				startMoveY = 2;
				startMoveX = 0;
				endMoveY = -1;
				endMoveX = 4;
				toMoveY = 1;
				toMoveX = 0;
				changeY = -1;
				changeX = 1;
				x = 0;
				y = (int)(rnd.nextInt(100) % 4);
				break;
			case 2:
				startMoveY = 0;
				startMoveX = 1;
				endMoveY = 4;
				endMoveX = 4;
				toMoveY = 0;
				toMoveX = -1;
				changeY = 1;
				changeX = 1;
				x = (int)(rnd.nextInt(100) % 4);
				y = 3;
		    	break;
			case 3:
				startMoveY = 0;
				startMoveX = 2;
				endMoveY = 4;
				endMoveX = -1;
				toMoveY = 0;
				toMoveX = 1;
				changeY = 1;
				changeX = -1;
				x = (int)(rnd.nextInt(100) % 4);
				y = 0;
				break;
		}
		//1マスずつ計3回移動処理を行う
		cnt = 0;
		while(cnt < 3){
			for(i = startMoveY; i != endMoveY; i += changeY){
				s = i + toMoveY;
				for(j = startMoveX; j != endMoveX; j += changeX){
					t = j + toMoveX;
					//移動元が0でないとき
					if(field[i][j] != 0){
						//移動元と移動先の値が同じまたは移動先が0
						if(field[i][j] == field[s][t] || field[s][t] == 0){
							if(field[i][j] == field[s][t]){
								//フィールド値をスコアに加算
								score += field[s][t];
								//くっつける([2][2] ⇒ [4],[4][4] ⇒ [8]...)
								field[s][t] *= 2;
							}else{
								field[s][t] = field[i][j];
							}
							field[i][j] = 0;
						}
					}
				}
			}
			cnt++;
			//スコアviewの更新
			tv.setText("*" + score);
		}

		sp.play(sound_id, 1.0F, 1.0F, 0, 0, 1.0F);

		//ポップ位置が空白の時だけ2をポップ
		if(field[x][y] == 0){
			field[x][y] = 2;
		}
		//フィールドviewの更新
		refleshImage();
	}

	//--------------------------------------------------------------------------
	//フィールド画像の更新メソッド
	//--------------------------------------------------------------------------
	private static void refleshImage(){
		int a, b;
		int num, id;
		for(a = 0; a < 4; a++){
			for(b = 0; b < 4; b++){
				num = field[a][b];
				id = 0;
				//フィールド値に対応するidを判別
				while(num >= 2){
					num /= 2;
					id++;
				}
				iv[a * 4 + b].setImageResource(resId[id]);
			}
		}
	}
}


