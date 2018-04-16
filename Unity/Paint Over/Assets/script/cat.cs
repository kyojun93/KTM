using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cat : MonoBehaviour {

    public enum CatState
    {
        IDLE,
        WALK,
    }
    public AudioClip m_JumpSound;
    private Animator m_animator;
    public Rigidbody2D m_rigidbody;
    private Vector3 m_left = new Vector3(-1, 1, 1);
    private Vector3 m_charDir = Vector3.zero;
    private SpriteRenderer m_spriteRender;
    public bool m_isKey = false;
    public List<cloud> m_coudList = new List<cloud>();
    private Vector3 m_beforeTransfer;
    private Vector3 m_beforeScale;
    public Color GCOLOR
    {
        get { return m_spriteRender.color; }
        set { m_spriteRender.color = value; }
    }
    private void Start()
    {
        m_animator = GetComponent<Animator>();
        m_rigidbody = GetComponent<Rigidbody2D>();
        Transform flag = transform.Find("flag");
        if (flag != null)
        {
            m_spriteRender = flag.GetComponent<SpriteRenderer>();
        }
        GameObject CloudGroup = GameObject.Find("Clouds");
        if (CloudGroup != null)
        {
            m_coudList.AddRange(CloudGroup.GetComponentsInChildren<cloud>(true));
        }
    }
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            m_animator.SetInteger("state", (int)CatState.WALK);
            transform.localScale = m_left;
        }

        if (Input.GetKeyDown(KeyCode.D))
        {
            m_animator.SetInteger("state", (int)CatState.WALK);
            transform.localScale = Vector3.one;
        }

        //Debug.Log(m_rigidbody.velocity.y);

       
        if (Input.GetKeyDown(KeyCode.Space) && !(m_rigidbody.velocity.y < 0 || m_rigidbody.velocity.y > 0))
        {
            GetComponent<AudioSource>().PlayOneShot(m_JumpSound);
            m_animator.SetTrigger("jump");
            m_rigidbody.AddForce(transform.up * 300);

        }

        if (Input.GetKey(KeyCode.A))
        {
            m_charDir = m_rigidbody.velocity;
            m_charDir.x = -2;
            m_rigidbody.velocity = m_charDir;
        }

        if (Input.GetKey(KeyCode.D))
        {
            m_charDir = m_rigidbody.velocity;
            m_charDir.x = 2;
            m_rigidbody.velocity = m_charDir;
        }

        if (!Input.GetKey(KeyCode.A) && !Input.GetKey(KeyCode.D))
        {
            m_charDir = m_rigidbody.velocity;
            m_charDir.x = 0;
            m_rigidbody.velocity = m_charDir;

            //m_animator.SetInteger("state", (int)CatState.IDLE);
        }
    }
    private void Switch(bool state)
    {
        this.enabled = state;
        GetComponent<BoxCollider2D>().enabled = state;
        GetComponent<CircleCollider2D>().enabled = state;
        m_rigidbody.simulated = state;
    }

    public void Stop()
    {
        m_beforeTransfer = transform.position;
        m_beforeScale = transform.localScale;
        Switch(false);
    }

    public void Resume()
    {
        transform.position = GameObject.Find("StartPoint").transform.position;
        transform.localScale = m_beforeScale;
        transform.rotation = Quaternion.Euler(0, 0, 0);
        Switch(true);

    }
}
