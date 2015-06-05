/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONObject;
import com.easyndk.classes.AndroidNDKHelper;
import com.tools.ImageOperate;
import android.content.Intent;
import android.graphics.*;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;

import org.json.JSONException;

public class AppActivity extends Cocos2dxActivity {
	private static final int IMAGE_REQUEST_CODE = 0;
	private static final int CAMERA_REQUEST_CODE = 1;
	private static final int RESULT_REQUEST_CODE = 2;
	private String _filePath;
	private String _fileName;
	private static final String TEMPFILENAME = "faceImage.jpg";
	private String TEMP_DIR;

	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AndroidNDKHelper.SetNDKReciever(this);
		TEMP_DIR = getExternalCacheDir().getPath() + '/';
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// 可能会出现取消的情况
		if (resultCode != RESULT_CANCELED) {

			switch (requestCode) {
			case IMAGE_REQUEST_CODE: {
				Uri uri = data.getData();
				if (null != uri) {
					if (ImageOperate.saveImagePNG(this, data, _filePath + _fileName)){
						AndroidNDKHelper.SendMessageWithParameters("showFaceImage",
								_filePath + _fileName);
					}
				}
			}
				break;
			case CAMERA_REQUEST_CODE: {
				// saveImagePNG(data);
				File tempFile = new File(TEMP_DIR,
						TEMPFILENAME);
				if (tempFile.exists()){
					if (ImageOperate.saveImagePNG(
							TEMP_DIR + TEMPFILENAME,
							_filePath + _fileName)){
						AndroidNDKHelper.SendMessageWithParameters("showFaceImage",
								_filePath + _fileName);
					}
					tempFile.delete();
				}
			}
				break;
			case RESULT_REQUEST_CODE:
				Log.v("SampleSelector", "purchase something called");
				break;
			}
		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	public void Gallery_Cpp(JSONObject prms) {
		try {
			_filePath = prms.getString("filePath");
			_fileName = prms.getString("fileName");
		} catch (JSONException e) {
			e.printStackTrace();
		}
//		Intent intentFromGallery = new Intent();
//		intentFromGallery.setType("image/*"); // 设置图片类型
//		intentFromGallery.setAction(Intent.ACTION_GET_CONTENT);
//		Intent intentFromGallery = new Intent(Intent.ACTION_PICK,
//		android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
//		startActivityForResult(intentFromGallery, IMAGE_REQUEST_CODE);
		
		Intent intentFromGallery=new Intent(Intent.ACTION_GET_CONTENT);//ACTION_OPEN_DOCUMENT  
		intentFromGallery.addCategory(Intent.CATEGORY_OPENABLE);  
		intentFromGallery.setType("image/*");
		startActivityForResult(intentFromGallery, IMAGE_REQUEST_CODE);
	}

	public void Camera_CPP(JSONObject prms) {
		try {
			_filePath = prms.getString("filePath");
			_fileName = prms.getString("fileName");
		} catch (JSONException e) {
			e.printStackTrace();
		}
		if (null != TEMP_DIR && null != TEMPFILENAME) {
			Intent intentFromCapture = new Intent(
					MediaStore.ACTION_IMAGE_CAPTURE);
			File out = new File(TEMP_DIR, TEMPFILENAME);
			if (out.exists()) {
				out.delete();
			}
			intentFromCapture.putExtra(MediaStore.EXTRA_OUTPUT,
					Uri.fromFile(out));
			startActivityForResult(intentFromCapture,
					CAMERA_REQUEST_CODE);
		}
	}

	public void ClipPNG_CPP(JSONObject prms) {
		try {
			String Src = prms.getString("Src");
			String Clip = prms.getString("Clip").substring(7);
			savePNGByClip(Src, Clip);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public void savePNGByClip(String Src, String Clip) {
		try {
			Bitmap src, clip;
			src = BitmapFactory.decodeFile(Src);
			InputStream is = getAssets().open(Clip);
			clip = BitmapFactory.decodeStream(is);
			is.close();
			if (ImageOperate.savePNGByClip(src,
					clip,
					_filePath + "Clip.png")){
				AndroidNDKHelper.SendMessageWithParameters("showFaceImage",
						_filePath + "Clip.png");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
