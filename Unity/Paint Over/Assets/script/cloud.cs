using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cloud : MonoBehaviour {
    public SpriteRenderer m_SpriteRenderer;
    public BoxCollider2D ColliderOJ;
    public BoxCollider2D TrigetOJ;
    public Color m_color = Color.white;
    public bool m_Fix = false;
    private cat Cat;
    // Use this for initialization
    void Start()
    {
        if(m_SpriteRenderer != null)
            m_SpriteRenderer.color = m_color;
    }
	
	// Update is called once per frame
	void Update () {
        if (m_SpriteRenderer != null)
            m_color= m_SpriteRenderer.color;
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //Debug.Log("Enter");
        if (collision.tag.Equals("Player"))
             Physics2D.IgnoreCollision(ColliderOJ, collision, true);
      //  ColliderOJ.enabled = true;
       // Physics2D.IgnoreCollision(ColliderOJ, TrigetOJ, false);
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
       // Debug.Log("Exit");
        if(collision.tag.Equals("Player"))
            Physics2D.IgnoreCollision(ColliderOJ, collision, false);
        //ColliderOJ.enabled = false;
       // Physics2D.IgnoreCollision(ColliderOJ, TrigetOJ, true);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        Cat = collision.transform.GetComponent<cat>();
        if(Cat != null)
        {
            if (Cat.GCOLOR.Equals(m_SpriteRenderer.color))
            {
                if (!m_Fix)
                {
                    Physics2D.IgnoreCollision(ColliderOJ, collision.collider, true);
                }
                return;
            }
            if (!m_Fix && Cat.m_rigidbody.velocity.y == 0)
                m_SpriteRenderer.color = Cat.GCOLOR;
        }
    }
}
