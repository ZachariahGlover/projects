using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour {

    public Transform target;

    public float distance = 5.0f;

    public float xSpeed = 40.0f;
    public float ySpeed = 40.0f;
    public float dampening = 0.25f;
 
    public float yMinLimit = -20f;
    public float yMaxLimit = 80f;
 
    public float distanceMin = 2.0f;
    public float distanceMax = 8.0f;

    public float offsetX = 0.0f;
    public float offsetY = 20.0f;

    private float x = 0.0f;
    private float y = 0.0f;

    void Start() {
    	Vector3 angles = transform.eulerAngles;
        x = angles.y;
        y = angles.x;
    }

    void LateUpdate() {
    	if (Input.GetMouseButton(1)) {
	    	x += Input.GetAxis("Mouse X") * xSpeed * distance * 0.02f;
	        y -= Input.GetAxis("Mouse Y") * ySpeed * 0.02f;
	        y = ClampAngle(y, yMinLimit, yMaxLimit);
	        Quaternion rotation = Quaternion.Euler(y, x, 0);
	        distance = Mathf.Clamp(distance - Input.GetAxis("Mouse ScrollWheel")*5, distanceMin, distanceMax);
	        Vector3 negDistance = new Vector3(0.0f, 0.0f, -distance);
	        Vector3 position = rotation * negDistance + target.position;
	        transform.rotation = rotation;
	        transform.position = position;
    	} else {
			x = Mathf.LerpAngle(transform.eulerAngles.y, target.eulerAngles.y + offsetX, dampening);
	        y = Mathf.LerpAngle(transform.eulerAngles.x, offsetY, dampening);
	        Quaternion rotation = Quaternion.Euler(y, x, 0);
	        distance = Mathf.Clamp(distance - Input.GetAxis("Mouse ScrollWheel")*5, distanceMin, distanceMax);
	        Vector3 negDistance = new Vector3(0.0f, 0.0f, -distance);
	        Vector3 position = rotation * negDistance + target.position;
	        transform.rotation = rotation;
	        transform.position = position;
    	}
    }

    public static float ClampAngle(float angle, float min, float max) {
        if (angle < -360F) { angle += 360F; }
        if (angle > 360F) { angle -= 360F; }
        return Mathf.Clamp(angle, min, max);
    }

}
