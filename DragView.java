package ie14.K.Nishim;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class DragView extends View{

	private Bitmap mBitmap;
	private Bitmap stamp_img;
	private Canvas mCanvas;


	// 最後にタッチされた座標
	float startTouchX;
	float startTouchY;

	// 現在タッチ中の座標
	float nowTouchedX = 0;
	float nowTouchedY = 0;

	// フリックの遊び部分（最低限移動しないといけない距離）
	float adjust = 120;

	// コンストラクタ
	public DragView(Context context) {
		super(context);
	    stamp_img = BitmapFactory.decodeResource(getResources(), R.drawable.shine);
	}

	// 画面変更時
	protected void onSizeChanged(int w, int h, int oldw, int oldh){
	    //キャンバス作成
	    mBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
	    mCanvas = new Canvas(mBitmap);
	}

	// 描画関数
	@Override
	protected void onDraw(Canvas canvas) {
	    canvas.drawBitmap(mBitmap, 0, 0, null);
	}

	// タッチされた時
	public boolean onTouchEvent(MotionEvent event) {

		float drawX = event.getX();
		float drawY = event.getY
				();
		switch (event.getAction()) {
			// タッチ
			case MotionEvent.ACTION_DOWN:
				startTouchX = event.getX();
				startTouchY = event.getY();
				break;

			// スライド
			case MotionEvent.ACTION_MOVE:
				mCanvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
				mCanvas.drawBitmap( stamp_img , drawX, drawY, null);
				invalidate();
				break;

			// タッチが離れた
			case MotionEvent.ACTION_UP:
				mCanvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
				nowTouchedX = event.getX();
				nowTouchedY = event.getY();
				if( startTouchY > nowTouchedY ){
					if( startTouchX > nowTouchedX ){
						if( ( startTouchY - nowTouchedY ) > ( startTouchX - nowTouchedX ) ){
							if( startTouchY > nowTouchedY + adjust ){
								Log.v( "Flick", "--上" );
								// 上フリック時の処理
								Ing.FlickEvent(0);
							}
						}
						else if( ( startTouchY - nowTouchedY ) < ( startTouchX - nowTouchedX ) ){
							if( startTouchX > nowTouchedX + adjust ){
								Log.v( "Flick", "--左" );
								// 左フリック時の処理
								Ing.FlickEvent(2);
							}
						}
					}
					else if( startTouchX < nowTouchedX ){
						if( ( startTouchY - nowTouchedY ) > ( nowTouchedX - startTouchX ) ){
							if( startTouchY > nowTouchedY + adjust ){
								Log.v( "Flick", "--上" );
								// 上フリック時の処理
								Ing.FlickEvent(0);
							}
						}
						else if( ( startTouchY - nowTouchedY ) < ( nowTouchedX - startTouchX ) ){
							if( startTouchX < nowTouchedX + adjust ){
								Log.v( "Flick", "--右" );
								// 右フリック時の処理
								Ing.FlickEvent(3);
							}
						}
					}
				}
				else if( startTouchY < nowTouchedY ){
					if( startTouchX > nowTouchedX ){
						if( ( nowTouchedY - startTouchY ) > ( startTouchX - nowTouchedX ) ){
							if( startTouchY < nowTouchedY + adjust ){
								Log.v( "Flick", "--下" );
								// 下フリック時の処理
								Ing.FlickEvent(1);
							}
						}
						else if( ( nowTouchedY - startTouchY ) < ( startTouchX - nowTouchedX ) ){
							if( startTouchX > nowTouchedX + adjust ){
								Log.v( "Flick", "--左" );
								// 左フリック時の処理
								Ing.FlickEvent(2);
							}
						}
					}
					else if( startTouchX < nowTouchedX ){
						if( ( nowTouchedY - startTouchY ) > (  nowTouchedX - startTouchX  ) ){
							if( startTouchY < nowTouchedY + adjust ){
								Log.v( "Flick", "--下" );
								// 下フリック時の処理
								Ing.FlickEvent(1);
							}
						}
						else if( ( nowTouchedY - startTouchY ) < ( nowTouchedX - startTouchX ) ){
							if( startTouchX < nowTouchedX + adjust ){
								Log.v( "Flick", "--右" );
								// 右フリック時の処理
								Ing.FlickEvent(3);
							}
						}
					}
				}
				break;

			// アップ後にほかの指がタッチ中の場合
			case MotionEvent.ACTION_POINTER_UP:
				Log.v( "motionEvent", "--ACTION_POINTER_UP" );
				break;

			// UP+DOWNの同時発生(タッチのキャンセル）
			case MotionEvent.ACTION_CANCEL:
				Log.v( "motionEvent", "--ACTION_CANCEL" );

			// ターゲットとするUIの範囲外を押下
			case MotionEvent.ACTION_OUTSIDE:
				Log.v( "motionEvent", "--ACTION_OUTSIDE" );
				break;
		}
		return true;
	}
}
