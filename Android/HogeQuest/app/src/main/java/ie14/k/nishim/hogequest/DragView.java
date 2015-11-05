package ie14.k.nishim.hogequest;

/**
 * Created by ie14 on 2015/11/05.
 */

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.PorterDuff;
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

    // コンストラクタ
    public DragView(Context context) {
        super(context);
        stamp_img = BitmapFactory.decodeResource(getResources(), R.drawable.drag);
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
                break;
        }
        return true;
    }
}