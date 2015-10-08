package ie14.K.Nishim;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

public class Main2048 extends Activity {


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main2048);

		ImageButton ib = (ImageButton)findViewById(R.id.buttonTitle);
		ib.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent(Main2048.this, Ing.class);
				startActivity(intent);
			}
		});
	}
}

