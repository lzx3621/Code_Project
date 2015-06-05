package com.tools;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.R.string;
import android.annotation.TargetApi;
import android.content.ContentUris;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.PorterDuff.Mode;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.DocumentsContract;
import android.provider.MediaStore;

public class ImageOperate {
	//版本比较：是否是4.4及以上版本
	static final boolean mIsKitKat = Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT;
	public static boolean saveImagePNG(String path, String saveNamePath) {
		if (null != path) {
			return saveImagePNG(getBitmapFromFile(new File(path), 720, 1280), saveNamePath);
		}
		return false;
	}
	
	public static boolean saveImagePNG(Bitmap photo, String saveNamePath) {
		if (null != photo) {
			try {
				Bitmap save;
				int width = photo.getWidth();
				int height = photo.getHeight();
				float widthScale = width / 720.0f;
				float heightScale = height / 1280.0f;
				if (width < 720 && height < 1280) {
					save = photo;
				} else {
					float Scale = widthScale > heightScale ? heightScale
							: widthScale;
					width = (int) (width / Scale);
					height = (int) (height / Scale);
					save = Bitmap
							.createScaledBitmap(photo, width, height, true);
					photo.recycle();
				}
				BufferedOutputStream bos = new BufferedOutputStream(
						new FileOutputStream(saveNamePath, false));
				save.compress(Bitmap.CompressFormat.PNG, 100, bos);
				bos.flush();
				bos.close();
				save.recycle();
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
			return true;
		}
		return false;
	}
	
	public static boolean saveImagePNG(final Context context, Intent data, String saveNamePath) {
		Uri uri = data.getData();
		if (null == uri) {
			try {
				Bundle bundle = data.getExtras();
				Bitmap photo = (Bitmap) bundle.get("data");
				return saveImagePNG(photo, saveNamePath);
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
		} else {
//			try {
//				return saveImagePNG(
//						BitmapFactory.decodeStream(context.getContentResolver().openInputStream(uri)),
//						saveNamePath);
//			} catch (FileNotFoundException e) {
//				e.printStackTrace();
//			}
			String path = null;
			if (mIsKitKat){
				path = getPathKitKat(context, uri);
			}else{
				path = getPath(context, uri);
			}
			return saveImagePNG(path, saveNamePath);
		}
	}
	
	public static boolean savePNGByClip(Bitmap Src, Bitmap Clip, String saveNamePath) {
		Bitmap draw = Clip.copy(Bitmap.Config.ARGB_8888, true);
		Canvas canvas = new Canvas(draw);
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setXfermode(new PorterDuffXfermode(Mode.SRC_IN));
		canvas.drawBitmap(Src, 0, 0, paint);
		try {
			BufferedOutputStream bos = new BufferedOutputStream(
					new FileOutputStream(saveNamePath, false));
			draw.compress(Bitmap.CompressFormat.PNG, 100, bos);
			bos.flush();
			bos.close();
			draw.recycle();
			return true;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return false;
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}
	}
	
	public static int calculateInSampleSize(BitmapFactory.Options op, int reqWidth,
			int reqheight) {
		int originalWidth = op.outWidth;
		int originalHeight = op.outHeight;
		int inSampleSize = 1;
		if (originalWidth > reqWidth || originalHeight > reqheight) {
			while (((originalWidth/inSampleSize) > reqWidth)
					|| ((originalHeight/inSampleSize) > reqheight)) {
				inSampleSize += 1;
			}
		}
		return inSampleSize;
	}

	public static Bitmap getBitmapFromFile(File dst, int width, int height) {
		if (null != dst && dst.exists()) {
			BitmapFactory.Options opts = null;
			if (width > 0 && height > 0) {
				opts = new BitmapFactory.Options();
				opts.inJustDecodeBounds = true;
				BitmapFactory.decodeFile(dst.getPath(), opts);
				// 计算图片缩放比例
				opts.inPreferredConfig = Bitmap.Config.ARGB_4444;
				opts.inSampleSize = calculateInSampleSize(opts, width, height);
				opts.inJustDecodeBounds = false;
				opts.inInputShareable = true;
				opts.inPurgeable = true;
			}
			return BitmapFactory.decodeFile(dst.getPath(), opts);
		}else{
			return null;
		}
	}
	
	@TargetApi(Build.VERSION_CODES.KITKAT)
	public static String getPathKitKat(final Context context, final Uri uri) {
        if (null == context || null == uri)
        {
        	return null;
        }
		final boolean isKitKat = Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT;

		// DocumentProvider
		if (isKitKat && DocumentsContract.isDocumentUri(context, uri)) {
			// ExternalStorageProvider
			if (isExternalStorageDocument(uri)) {
				final String docId = DocumentsContract.getDocumentId(uri);
				final String[] split = docId.split(":");
				final String type = split[0];

				if ("primary".equalsIgnoreCase(type)) {
					return Environment.getExternalStorageDirectory() + "/" + split[1];
				}
			}
			// DownloadsProvider
			else if (isDownloadsDocument(uri)) {

				final String id = DocumentsContract.getDocumentId(uri);
				final Uri contentUri = ContentUris.withAppendedId(
						Uri.parse("content://downloads/public_downloads"), Long.valueOf(id));

				return getDataColumn(context, contentUri, null, null);
			}
			// MediaProvider
			else if (isMediaDocument(uri)) {
				final String docId = DocumentsContract.getDocumentId(uri);
				final String[] split = docId.split(":");
				final String type = split[0];

				Uri contentUri = null;
				if ("image".equals(type)) {
					contentUri = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
				} else if ("video".equals(type)) {
					contentUri = MediaStore.Video.Media.EXTERNAL_CONTENT_URI;
				} else if ("audio".equals(type)) {
					contentUri = MediaStore.Audio.Media.EXTERNAL_CONTENT_URI;
				}

				final String selection = "_id=?";
				final String[] selectionArgs = new String[] { split[1] };

				return getDataColumn(context, contentUri, selection, selectionArgs);
			}
		}
		// MediaStore (and general)
		else if ("content".equalsIgnoreCase(uri.getScheme())) {

			// Return the remote address
			if (isGooglePhotosUri(uri))
				return uri.getLastPathSegment();

			return getDataColumn(context, uri, null, null);
		}
		// File
		else if ("file".equalsIgnoreCase(uri.getScheme())) {
			return uri.getPath();
		}

		return null;
	}

	public static String getDataColumn(Context context, Uri uri, String selection,
			String[] selectionArgs) {

		Cursor cursor = null;
		final String column = "_data";
		final String[] projection = { column };

		try {
			cursor = context.getContentResolver().query(uri, projection, selection, selectionArgs,
					null);
			if (cursor != null && cursor.moveToFirst()) {
				final int index = cursor.getColumnIndexOrThrow(column);
				return cursor.getString(index);
			}
		} finally {
			if (cursor != null)
				cursor.close();
		}
		return null;
	}

	/**
	 * @param uri The Uri to check.
	 * @return Whether the Uri authority is ExternalStorageProvider.
	 */
	public static boolean isExternalStorageDocument(Uri uri) {
		return "com.android.externalstorage.documents".equals(uri.getAuthority());
	}

	/**
	 * @param uri The Uri to check.
	 * @return Whether the Uri authority is DownloadsProvider.
	 */
	public static boolean isDownloadsDocument(Uri uri) {
		return "com.android.providers.downloads.documents".equals(uri.getAuthority());
	}

	/**
	 * @param uri The Uri to check.
	 * @return Whether the Uri authority is MediaProvider.
	 */
	public static boolean isMediaDocument(Uri uri) {
		return "com.android.providers.media.documents".equals(uri.getAuthority());
	}

	/**
	 * @param uri The Uri to check.
	 * @return Whether the Uri authority is Google Photos.
	 */
	public static boolean isGooglePhotosUri(Uri uri) {
		return "com.google.android.apps.photos.content".equals(uri.getAuthority());
	}
	public static String getPath(final Context context, final Uri uri){  
        if (null == context || null == uri)
        {
        	return null;
        }
        if(uri!=null){              
            String uriStr=uri.toString();  
            String path=uriStr.substring(10,uriStr.length());  
            if(path.startsWith("com.sec.android.gallery3d")){ 
                return null;  
            }  
        }
        String[] filePathColumn = { MediaStore.Images.Media.DATA };  
        Cursor cursor = context.getContentResolver().query(uri,filePathColumn, null, null, null);  
        cursor.moveToFirst();  
        int columnIndex = cursor.getColumnIndex(filePathColumn[0]);  
        String picturePath = cursor.getString(columnIndex);  
        cursor.close();  
        return picturePath;       
    }  
}
