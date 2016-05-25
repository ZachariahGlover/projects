using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour {

    public float deceleration = 0.1f;
    public float moveSpeed = 1.0f;
    public float jumpSpeed = 0.5f;
    public float turnSpeed = 1.0f;
    public float gravity = 9.8f;

    private CharacterController controller;
    private Vector3 direction;
    private Vector3 velocity;

    void Start() {
        controller = GetComponent<CharacterController>();
        direction = new Vector3(0.0f, 0.0f, 0.0f);
        velocity = new Vector3(0.0f, 0.0f, 0.0f);
    }

    void Move() {
        float rh = Input.GetAxis("Horizontal");
        float rv = Input.GetAxis("Vertical");
        float accel = 0.0f;

        if (rv > 0.0f) {
        	accel = moveSpeed * rv;
        	if (rh != 0.0f){
        		transform.rotation *= Quaternion.Euler(Vector3.up * (turnSpeed * rh));
            	direction = transform.rotation * Vector3.forward;
        	}
        } else if (rv < 0.0f) {
        	accel = moveSpeed * rv * 0.5f;
        	if (rh != 0.0f){
        		rh *= -1.0f;
        		transform.rotation *= Quaternion.Euler(Vector3.up * (turnSpeed * rh));
            	direction = transform.rotation * Vector3.forward;
        	}
        } else {
        	accel = moveSpeed * Mathf.Abs(rh) * deceleration;
        	transform.rotation *= Quaternion.Euler(Vector3.up * (turnSpeed * rh));
            direction = transform.rotation * Vector3.forward;
        }

        if (controller.isGrounded) {
            velocity.y = 0.0f;
            direction.y = 0.0f;
            velocity *= deceleration;
            if (Input.GetButton("Jump")) {
                direction.y = jumpSpeed;
            }
            velocity.x += direction.x * accel;
            velocity.y += gravity * direction.y;
            velocity.z = direction.z * accel;
        } else {
            velocity.y -= gravity * Time.deltaTime;
        }
        controller.Move(velocity * Time.deltaTime);
    }

    void Update() {
        Move();
    }

}
