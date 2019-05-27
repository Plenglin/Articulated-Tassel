package io.github.plenglin.articulatedtassel

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import org.slf4j.LoggerFactory

class MainActivity : AppCompatActivity() {

    //val bluetoothAdapter = Blue

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn_select_device.setOnClickListener {
            logger.info("Clicked on device selection")
        }
    }

    private companion object {
        @JvmStatic
        val logger = LoggerFactory.getLogger(MainActivity::class.java)
    }
}
